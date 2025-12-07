#ifndef _PAGING_H_
#define _PAGING_H_

#include "heap.h"

#include "../panic.h"
#include "../isr.h"

#include "../lib/kint.h"
#include "../lib/kstd.h"

#include "../lib/kstring.h"

#define HARD_MEMORY_LIMIT 0x1000000

#define PAGE_SIZE 0x1000

struct pde {
    uint32_t present       : 1;
    uint32_t rw            : 1;
    uint32_t us            : 1;
    uint32_t pwt           : 1;
    uint32_t pcd           : 1;
    uint32_t accessed      : 1;
    uint32_t reserved      : 6;
    uint32_t table_address : 20;
} __attribute__((packed));

typedef struct pde pde_t;

struct pte {
    uint32_t present       : 1;
    uint32_t rw            : 1;
    uint32_t us            : 1;
    uint32_t pwt           : 1;
    uint32_t pcd           : 1;
    uint32_t accessed      : 1;
    uint32_t dirty         : 1;
    uint32_t pat           : 1;
    uint32_t global        : 1;
    uint32_t reserved      : 3;
    uint32_t frame_address : 20;
} __attribute__((packed));

typedef struct pte pte_t;

struct page_table {
    uint32_t pages[1024];
} __attribute__((packed));

typedef struct page_table page_table_t;

struct page_dir {
    page_table_t *logical_page_tables[1024];
    uint32_t phys_page_tables[1024];
} __attribute__((packed));

typedef struct page_dir page_dir_t;

void init_paging(void);

#endif
