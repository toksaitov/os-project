# Constants

BIN_DIR = bin
ISO_DIR = iso

LOADER = loader
KERNEL = kernel

LINKER_SCRIPT = link

ISO_IMAGE = $(BIN_DIR)/boot.iso

ASM_SRC = $(LOADER).s          \
	  sys/isr_handler.s        \
	  sys/tables/gdt_handler.s \
	  sys/tables/idt_handler.s

C_SRC   = $(KERNEL).c \
	  sys/kio.c       \
	  sys/isr.c       \
	  sys/pic.c       \
	  sys/pit.c       \
	  sys/kbd.c       \
	  sys/panic.c     \
	  sys/display/display.c \
	  sys/tables/gdt.c      \
	  sys/tables/idt.c      \
	  sys/mm/heap.c         \
	  sys/mm/paging.c       \
	  sys/lib/kctypes.c     \
	  sys/lib/kstd.c        \
	  sys/lib/kstring.c

ASM_OBJECTS = $(ASM_SRC:.s=.o)
C_OBJECTS   = $(C_SRC:.c=.o)

# System Configuration

CC     = x86_64-elf-gcc
CFLAGS = -m32 -mno-sse -mno-sse2 -g -Wall -Wextra -ansi -nostdlib -nostartfiles -nodefaultlibs

LD      = x86_64-elf-ld
LDFLAGS = -m elf_i386 -T $(LINKER_SCRIPT).ld

# General Rules

.PHONY : all
all : $(KERNEL)

# ISO Image Creation (requires Docker)

.PHONY : iso
iso : $(ISO_IMAGE)

$(ISO_IMAGE) : $(KERNEL)
	@mkdir -p $(BIN_DIR)
	@cp $(KERNEL) $(ISO_DIR)/boot/
	@docker run --rm --platform linux/amd64 -v "$(CURDIR)":/work -w /work ubuntu:24.04 sh -c \
		"apt-get update -qq && \
		 apt-get install -y -qq grub-pc-bin grub-common xorriso mtools >/dev/null 2>&1 && \
		 grub-mkrescue -o $(ISO_IMAGE) $(ISO_DIR) 2>/dev/null"
	@rm -f $(ISO_DIR)/boot/$(KERNEL)
	@echo "Created $(ISO_IMAGE)"

# Kernel

$(KERNEL) : $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

$(ASM_OBJECTS) : %.o : %.s
	$(CC) -m32 -g -c -o $@ $<

$(C_OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : clean
clean :
	rm -f $(ASM_OBJECTS) $(C_OBJECTS) $(KERNEL) $(ISO_IMAGE) $(ISO_DIR)/boot/$(KERNEL)
