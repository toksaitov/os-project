#ifndef _HEAP_H_
#define _HEAP_H_

#include "../lib/kint.h"
#include "../lib/kstd.h"

/*
 * A symbol which points to the end of the kernel image in physical address 
 * space
 */
extern uintptr_t k_phys_mem_end; /* ...defined in the linker script. */

/*
 * A memory pointer to the next free address in a physical address space
 */
extern uintptr_t mem_reserved_ptr;

/*
 * Initializes the kernel memory manager.
 */
void init_mm(void);

/*
 * Reserves 'size'-bytes of physical memory returning the pointer to it. 
 * If the 'align' option was set, the function will try to reserve memory 
 * space from a page-aligned address.
 */
uintptr_t mem_reserve(size_t size, bool align);

#endif
