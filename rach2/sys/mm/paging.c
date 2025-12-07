#include "paging.h"

page_dir_t *_kernel_dir;
page_dir_t *_curr_dir;

uint8_t *_frames;
size_t   _frames_number;

static void _page_fault_handler(isr_params_t params);

static void _load_page_dir(page_dir_t *dir);

void init_paging(void)
{
    unsigned int frame;

    uintptr_t tmp, phys_address,
                   table_index,
                   page_index;

    page_table_t *table;

    _frames_number = HARD_MEMORY_LIMIT / PAGE_SIZE; /* ToDo: use real limit. */
    _frames = (uint8_t *) mem_reserve(_frames_number, true);
    k_memset(_frames, 0, _frames_number);

    _kernel_dir = (page_dir_t *) mem_reserve(sizeof(page_dir_t), true);
    k_memset(_kernel_dir, 0, sizeof(page_dir_t));
    _curr_dir = _kernel_dir;

    phys_address = frame = 0;
    while (phys_address < mem_reserved_ptr + 0x100000) { /* Extra 1MB for post-init allocations */
        tmp = phys_address / PAGE_SIZE;

        table_index = tmp / 1024;
        page_index  = tmp % 1024;

        if (!(table = _curr_dir->logical_page_tables[table_index])) {
            tmp = mem_reserve(sizeof(page_table_t), true);
            table = (page_table_t *) tmp;

            k_memset(table, 0, sizeof(page_table_t));

            /* This page table is writable only by a supervisor.
             * Page table address | 'present' and 'rw' flags */
            _curr_dir->phys_page_tables[table_index] = tmp | 0x3;

            _curr_dir->logical_page_tables[table_index] = table;
        }

        if (frame == _frames_number) {
            k_panic("Failed to allocate a page frame. No more free frames.");
        } else {
            _frames[frame++] = 1;
        }

        /*
         * This page is writable only by a supervisor.
         * Page frame address | 'present' and 'rw' flags
         */
        table->pages[page_index] = phys_address | 0x3;

        phys_address += PAGE_SIZE;
    }

    register_isr_handler(14, &_page_fault_handler);

    _load_page_dir(_curr_dir);
}

static void _load_page_dir(page_dir_t *dir)
{
    uint32_t cr0;

    __asm__ __volatile__ ("mov %0, %%cr3" :: "r"(&dir->phys_page_tables));
    __asm__ __volatile__ ("mov %%cr0, %0" : "=r"(cr0));

    cr0 |= 0x80000000;

    __asm__ __volatile__ ("mov %0, %%cr0" :: "r"(cr0));
}

static void _page_fault_handler(isr_params_t params)
{
    uint32_t fault_address;
    __asm__ __volatile__("mov %%cr2, %0" : "=r"(fault_address));

    k_printf("Kernel message: page fault at 0x%X with error code 0x%X\n", fault_address, params.error_code);

    k_panic("Unrecoverable error: page fault while in kernel mode.");
}
