#include "paging.h"
#include "isr.h"
#include "monitor.h"
#include "buddy.h"

extern u32 k_dir_addr;
extern u32 kernel_end;

static void flush_page();

void page_fault(registers_t* regs)
{
    // A page fault has occurred.
    // The faulting address is stored in the CR2 register.
    u32 faulting_address;
    asm volatile ("mov %%cr2, %0" : "=r" (faulting_address));
    
    // The error code gives us details of what happened.
    int present   = !(regs->err_code & 0x1); // Page not present
    int rw = regs->err_code & 0x2;           // Write operation?
    int us = regs->err_code & 0x4;           // Processor was in user-mode?
    int reserved = regs->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    int id = regs->err_code & 0x10;          // Caused by an instruction fetch?

    // Output an error message.
    m_printf("Page fault! ( ");
    if (present) {m_printf("present ");}
    if (rw) {m_printf("read-only ");}
    if (us) {m_printf("user-mode ");}
    if (reserved) {m_printf("reserved ");}
    m_printf(") at %x - EIP: %x\n",faulting_address,regs->eip);

}

void ini_kernel_page( u32 vd, u32 pd, page_directory* dir){
    

    u32 dir_index  = vd >> 22;
    u32 table_index  = ( vd & 0x3FFFFF ) >> 12;

    p_dir_entry* dir_entry = &dir->tables[dir_index];

    if ( * (u32*)dir_entry == 0 ){
        dir_entry->user = 0;
        dir_entry->rw = 1;
        dir_entry->present = 1;
        int addr = k_malloc(1);
        if(addr == -1){
            //TODO  no more free memory
        }
        dir_entry->frame = ((u32)addr) >> 12;
        memset((u8*)addr, 0, 0x1000 );

    }
    page_table* table = (page_table*) ( (u32)dir_entry->frame << 12 );

    p_table_entry* page = &table->pages[table_index];

    page->frame = (u32)pd >>12 ;
    page->present=1;
    page->rw=1;
    page->user=0;
}

void ini_paging(){

    //ini page directory

    page_directory* k_dir = (page_directory*) &k_dir_addr;
    memset( (u8*) k_dir, 0, sizeof( k_dir ) );


    u32 begin = 0;
    u32 end_ = (u32)&kernel_end;
    while( begin < end_ ){
        
        ini_kernel_page( begin, begin, k_dir);
        begin+=0x1000;

    }

    //ini dir self
    k_dir->tables[1023].frame = (u32)k_dir >> 12;
    k_dir->tables[1023].present=1;
    k_dir->tables[1023].rw=1;
    k_dir->tables[1023].user=0;

    register_interrupt_handler(14, page_fault);

    listmem();
    flush_page();

}
static void flush_page(){

    asm volatile ("mov %0, %%cr3":: "r"((u32)&k_dir_addr));
    u32 cr0;
    asm volatile ("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile ("mov %0, %%cr0":: "r"(cr0));
}
void map_page( u32 vd, u32 pd ,int rw){

    page_directory* dir = (page_directory*)(0xFFFFF000);
 
    u32 dir_index  = vd >> 22;
    u32 table_index  = ( vd & 0x3FFFFF ) >> 12;
    
    p_dir_entry* dir_entry = &dir->tables[dir_index];

    if ( * (u32*)dir_entry == 0 ){
        dir_entry->user = 1;
        dir_entry->rw = 1;
        dir_entry->present = 1;
        int addr = k_malloc(1);
        if(addr == -1){
            //TODO  no more free memory
        }
        dir_entry->frame = ((u32)addr) >> 12;

        //apply the new table
        flush_page();

        //clear the new table
        memset((u8*)(0xFFC00000 +  0x1000 * dir_index), 0, 0x1000);
    }

    page_table* table = (page_table*)(0xFFC00000 +  0x1000 * dir_index);
    
    p_table_entry* page = &table->pages[table_index];

    page->frame = (u32)pd >>12 ;
    page->present=1;
    page->rw = rw;
    page->user=1;
    flush_page();
}
void clear_map(u32 vd){

    page_directory* dir = (page_directory*)(0xFFFFF000);
 
    u32 dir_index  = vd >> 22;
    u32 table_index  = ( vd & 0x3FFFFF ) >> 12;
    
    p_dir_entry* dir_entry = &dir->tables[dir_index];
    if ( * (u32*)dir_entry != 0 ){

        page_table* table = (page_table*)(0xFFC00000 +  0x1000 * dir_index);
        p_table_entry* page = &table->pages[table_index];
        if(*(u32*)page != 0)
            memset((u8*)page, 0, sizeof(p_table_entry));

    }
    flush_page();
}
