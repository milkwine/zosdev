// paging.h -- Defines the interface for and structures relating to paging.
//             Written for JamesM's kernel development tutorials.

#ifndef PAGING_H
#define PAGING_H

#include "common.h"
#include "isr.h"

typedef struct p_dir_entry_
{
    u32 present    : 1;   // Page present in memory
    u32 rw         : 1;   // Read-only if clear, readwrite if set
    u32 user       : 1;   // Supervisor level only if clear
    u32 pwt        : 1;
    u32 pcd        : 1;
    u32 accessed   : 1;   // Has the page been accessed since last refresh?
    u32 unused     : 6;   // Amalgamation of unused and reserved bits
    u32 frame      : 20;  // Frame address (shifted right 12 bits)
} p_dir_entry;

typedef struct p_table_entry_
{
    u32 present    : 1;   // Page present in memory
    u32 rw         : 1;   // Read-only if clear, readwrite if set
    u32 user       : 1;   // Supervisor level only if clear
    u32 pwt        : 1;
    u32 pcd        : 1;
    u32 accessed   : 1;   // Has the page been accessed since last refresh?
    u32 dirty      : 1;   // Has the page been written to since last refresh?
    u32 unused     : 5;   // Amalgamation of unused and reserved bits
    u32 frame      : 20;  // Frame address (shifted right 12 bits)
} p_table_entry;


typedef struct page_table_
{
    p_table_entry pages[1024];
} page_table;

typedef struct page_directory_
{
    p_dir_entry tables[1024];

} page_directory;

//before set up paging
void ini_paging();
void ini_kernel_page( u32 vd, u32 pd, page_directory* dir);

//common
page_directory* ini_page_dir();
page_table* ini_page_table();

//after set up paging
void map_page( u32 vd, u32 pd, int rw );
void clear_map( u32 vd );




#endif
