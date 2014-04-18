#include "paging.h"
#include "isr.h"
#include "monitor.h"
#include "kheap.h"

extern u32 k_dir_addr;
extern u32 end;

void page_fault(registers_t regs)
{
    // A page fault has occurred.
    // The faulting address is stored in the CR2 register.
    u32 faulting_address;
    asm volatile ("mov %%cr2, %0" : "=r" (faulting_address));
    
    // The error code gives us details of what happened.
    int present   = !(regs.err_code & 0x1); // Page not present
    int rw = regs.err_code & 0x2;           // Write operation?
    int us = regs.err_code & 0x4;           // Processor was in user-mode?
    int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

    // Output an error message.
    m_write("Page fault! ( ",INFO);
    if (present) {m_write("present ",FAIL);}
    if (rw) {m_write("read-only ",FAIL);}
    if (us) {m_write("user-mode ",FAIL);}
    if (reserved) {m_write("reserved ",FAIL);}
    m_write(") at ",INFO);
    m_putint(faulting_address);
    m_write(" - EIP: ",INFO);
    m_putint(regs.eip);
    m_write("\n",INFO);

}

void ini_kernel_page( u32 vd, u32 pd, page_directory* dir){
    
    //m_write("ini kernel page. map :",INFO);
    //m_putint(vd);
    //m_write("\n",INFO);

    u32 dir_index  = vd >> 22;
    u32 table_index  = ( vd & 0x3FFFFF ) >> 12;
    m_write("ini kernel page.(map:",INFO);
    m_putint(vd);
    m_write(" dir_index:",INFO);
    m_putint(dir_index);
    m_write(" table_index:",INFO);
    m_putint(table_index);
    p_dir_entry* dir_entry = &dir->tables[dir_index];

    if ( * (u32*)dir_entry == 0 ){
        dir_entry->user = 0;
        dir_entry->rw = 1;
        dir_entry->present = 1;
        dir_entry->frame = malloc_f() >> 12;

    }
    page_table* table = (page_table*) ( (u32)dir_entry->frame << 12 );
    m_write(" table_addr:",INFO);
    m_putint((u32)table);
    p_table_entry* page = &table->pages[table_index];
    m_write(" page_addr:",INFO);
    m_putint((u32)page);
    m_write(")\n",INFO);

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
    u32 end_ = (u32)&end;
    while( begin < end_ ){
        
        ini_kernel_page( begin, begin, k_dir);
        begin+=0x1000;

    }
    m_write("ini pages:",INFO);
    m_putint(begin / 0x1000);
    m_write("\n",INFO);

    ibreak();

    register_interrupt_handler(14, page_fault);

    m_write("kdir:",INFO);
    m_putint((u32)&k_dir_addr);

    m_write("  end:",INFO);
    m_putint((u32)&end);
    m_write("\n",INFO);

    ibreak();

    asm volatile ("mov %0, %%cr3":: "r"((u32)&k_dir_addr));
    u32 cr0;
    asm volatile ("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile ("mov %0, %%cr0":: "r"(cr0));

}
