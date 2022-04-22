#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>
#include <stdbool.h>

#define TABLE_REGION 0x400000

typedef uint32_t virtual_addr;
typedef uint32_t pte_t;
typedef uint32_t pde_t;


void paging_init();

/*
 * Allocates a physical block of memory and assigns it to the given
 * page entry then marks the entry as present
 */
bool page_alloc(pte_t* entry);

void page_free(pte_t* entry);


pte_t* page_table_get_entry(pte_t* table, virtual_addr addr);

/*
 * Returns a reference to the page directory entry corresponding to the
 * given virtual address contained within the given page directory
 */
pde_t* page_dir_get_entry(pde_t* directory, virtual_addr addr);


pde_t* page_dir_get_current();

/*
 * Map a physical address to a given virtual address by placing a page
 * in the table that lies in the appropriate directory entry
 */
void paging_map_page(void* physical, void* virtual);

/*
 * Map a table to the appropriate entry corresponding to the virtual
 * address in the current directory with the physical address
 * Return true if the page is mapped, false if already mapped
 */
bool paging_map_table(void* physical, void* virtual);

/*
 * Set the currently loaded paging directory to the new
 * given directory
 */
bool paging_switch_directory(pde_t* directory);

/*
 * Invalidate page entry that refers to the given virtual address
 */
void paging_invalidate_entry(virtual_addr address);

#endif
