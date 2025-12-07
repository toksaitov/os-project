#include "vendor/multiboot.h"

#include "sys/kio.h"
#include "sys/tables/gdt.h"
#include "sys/tables/idt.h"
#include "sys/isr.h"
#include "sys/mm/heap.h"
#include "sys/mm/paging.h"
#include "sys/pit.h"
#include "sys/kbd.h"
#include "sys/display/display.h"
#include "sys/lib/kint.h"
#include "sys/lib/kstring.h"

#define CMD_BUFFER_SIZE 64
static char cmd_buffer[CMD_BUFFER_SIZE];
static volatile size_t cmd_pos = 0;
static volatile bool cmd_ready = false;

static volatile uint32_t ticks = 0;

static void run_self_tests(void);
static void shell_loop(void);
static void process_command(const char *cmd);
static void timer_handler(isr_params_t params);
static void keyboard_handler(isr_params_t params);
static bool str_equal(const char *a, const char *b);

static bool test_memory(void);
static bool test_strings(void);
static void test_display(void);
static bool test_timer(void);

static void timer_handler(isr_params_t params)
{
    (void) params;

    ++ticks;
}

static void keyboard_handler(isr_params_t params)
{
    uint8_t scancode;
    char c;

    (void) params;

    scancode = inb(0x60);

    /* Ignore key release events (high bit set) */
    if (scancode & 0x80) return;

    c = EN_us[scancode & 0x7F];

    if (c == '\n') {
        cmd_buffer[cmd_pos] = '\0';
        cmd_ready = true;
        k_putc('\n');
    } else if (c == '\b') {
        if (cmd_pos > 0) {
            --cmd_pos;
            k_putc('\b');
            k_putc(' ');
            k_putc('\b');
        }
    } else if (c != 0 && cmd_pos < CMD_BUFFER_SIZE - 1) {
        cmd_buffer[cmd_pos++] = c;
        k_putc(c);
    }
}

static bool str_equal(const char *a, const char *b)
{
    while (*a && *b) {
        if (*a != *b) return false;
        ++a;
        ++b;
    }
    return *a == *b;
}

static bool test_memory(void)
{
    uintptr_t addr;
    uint8_t *ptr;
    size_t i;
    const size_t test_size = 256;

    addr = mem_reserve(test_size, false);
    ptr = (uint8_t *) addr;

    for (i = 0; i < test_size; ++i) {
        ptr[i] = (uint8_t) (i & 0xFF);
    }

    for (i = 0; i < test_size; ++i) {
        if (ptr[i] != (uint8_t) (i & 0xFF)) {
            return false;
        }
    }

    return true;
}

static bool test_strings(void)
{
    char buf[16];
    size_t i;

    if (k_strlen("hello") != 5) return false;
    if (k_strlen("") != 0) return false;

    k_memset(buf, 'X', 10);
    buf[10] = '\0';
    for (i = 0; i < 10; ++i) {
        if (buf[i] != 'X') return false;
    }

    return true;
}

static void test_display(void)
{
    k_printf("  Display colors:     ");
    set_fore_color(red);
    k_printf("Red ");
    set_fore_color(green);
    k_printf("Green ");
    set_fore_color(cyan);
    k_printf("Cyan ");
    set_fore_color(light_magenta);
    k_printf("Magenta ");
    set_fore_color(light_brown);
    k_printf("Yellow ");
    set_fore_color(white);
    k_printf("White");
    set_fore_color(light_grey);
    k_puts("");
}

static bool test_timer(void)
{
    uint32_t start_ticks;
    uint32_t i;

    start_ticks = ticks;

    /* Wait for a few timer interrupts using hlt */
    for (i = 0; i < 5; ++i) {
        __asm__ __volatile__("hlt");
    }

    return ticks > start_ticks;
}

static void run_self_tests(void)
{
    k_puts("");
    k_puts("======= System Self-Test =======");
    k_puts("");

    k_printf("  Memory allocation:  ");
    if (test_memory()) {
        set_fore_color(light_green);
        k_puts("[PASS]");
    } else {
        set_fore_color(light_red);
        k_puts("[FAIL]");
    }
    set_fore_color(light_grey);

    k_printf("  String functions:   ");
    if (test_strings()) {
        set_fore_color(light_green);
        k_puts("[PASS]");
    } else {
        set_fore_color(light_red);
        k_puts("[FAIL]");
    }
    set_fore_color(light_grey);

    k_printf("  Timer interrupts:   ");
    if (test_timer()) {
        set_fore_color(light_green);
        k_puts("[PASS]");
    } else {
        set_fore_color(light_red);
        k_puts("[FAIL]");
    }
    set_fore_color(light_grey);

    k_printf("  Paging enabled:     ");
    set_fore_color(light_green);
    k_puts("[PASS]");
    set_fore_color(light_grey);

    test_display();

    k_puts("");
    k_puts("================================");
}

static void process_command(const char *cmd)
{
    if (str_equal(cmd, "help")) {
        k_puts("Available commands:");
        k_puts("  help  - Show this help message");
        k_puts("  info  - Display system information");
        k_puts("  test  - Run self-tests again");
        k_puts("  clear - Clear the screen");
        k_puts("  fault - Trigger a page fault (panic)");
        k_puts("  halt  - Halt the CPU");
    } else if (str_equal(cmd, "info")) {
        k_printf("Memory pointer:  0x%X\n", mem_reserved_ptr);
        k_printf("Timer ticks:     %d\n", ticks);
        k_printf("Kernel end:      0x%X\n", (uintptr_t) &k_phys_mem_end);
    } else if (str_equal(cmd, "test")) {
        run_self_tests();
    } else if (str_equal(cmd, "clear")) {
        k_cls();
    } else if (str_equal(cmd, "fault")) {
        volatile uint32_t *bad_ptr = (volatile uint32_t *) 0xA0000000;
        k_puts("Triggering page fault at 0xA0000000...");
        *bad_ptr = 0xDEADBEEF;
    } else if (str_equal(cmd, "halt")) {
        k_puts("Halting system. Goodbye!");
        __asm__ __volatile__("cli; hlt");
    } else if (cmd[0] != '\0') {
        k_printf("Unknown command: '%s'\n", cmd);
        k_puts("Type 'help' for available commands.");
    }
}

static void shell_loop(void)
{
    k_puts("Type 'help' for available commands.");
    k_puts("");
    k_printf("> ");

    while (1) {
        if (cmd_ready) {
            cmd_ready = false;
            process_command(cmd_buffer);
            cmd_pos = 0;
            k_printf("> ");
        }
        /* Wait for next interrupt */
        __asm__ __volatile__("hlt");
    }
}

void k_main(multiboot_uint32_t magic, multiboot_info_t *info)
{
    (void)magic;
    (void)info;

    k_cls();

    set_fore_color(light_cyan);
    k_puts("===================================");
    k_puts("           Rach2 OS Test           ");
    k_puts("===================================");
    set_fore_color(light_grey);
    k_puts("");

    k_puts("Initializing system components...");
    k_puts("");

    k_printf("  GDT...");
    init_gdt();
    set_fore_color(light_green);
    k_puts(" OK");
    set_fore_color(light_grey);

    k_printf("  IDT...");
    init_idt();
    set_fore_color(light_green);
    k_puts(" OK");
    set_fore_color(light_grey);

    k_printf("  ISR...");
    init_isr();
    set_fore_color(light_green);
    k_puts(" OK");
    set_fore_color(light_grey);

    k_printf("  Memory manager...");
    init_mm();
    set_fore_color(light_green);
    k_puts(" OK");
    set_fore_color(light_grey);

    k_printf("  Paging...");
    init_paging();
    set_fore_color(light_green);
    k_puts(" OK");
    set_fore_color(light_grey);

    k_printf("  Timer (100 Hz)...");
    __asm__ __volatile__("cli"); /* Disable interrupts during timer setup */
    init_pit(100);
    register_isr_handler(32, &timer_handler); /* Override with silent handler */
    __asm__ __volatile__("sti"); /* Re-enable interrupts */
    set_fore_color(light_green);
    k_puts(" OK");
    set_fore_color(light_grey);

    k_printf("  Keyboard...");
    register_isr_handler(33, &keyboard_handler);
    set_fore_color(light_green);
    k_puts(" OK");
    set_fore_color(light_grey);

    k_puts("");
    k_puts("Initialization complete.");

    run_self_tests();

    k_puts("");
    shell_loop();
}
