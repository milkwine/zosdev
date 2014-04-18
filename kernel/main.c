#include "common.h"
#include "monitor.h"
#include "descriptor.h"
#include "timer.h"
#include "multiboot.h"
#include "paging.h"
#include "common.h"
#include "kheap.h"

void kernel_main(multiboot_head_t *mboot_ptr){

    ini_descriptor();
    m_clear();

    
    //show_mem(mboot_ptr);
    //asm volatile("int $0x22");
    asm volatile("sti");
    //ini_timer(1);    
    ini_paging();
    m_write("ini paging kernel over\n", SUC);
    //ibreak();
    //u32 *ptr = (u32*)0xA0000000;
    //u32 do_page_fault = *ptr;
}
void show_mem(multiboot_head_t *mboot_ptr){

    m_write("flag:",INFO);
    m_putint( mboot_ptr->flags );
    m_write("\n",INFO);
    m_write("addr:",INFO);
    m_putint( mboot_ptr->mmap_addr );
    m_write("\n",INFO);
    m_write("len:",INFO);
    m_putint( mboot_ptr->mmap_length );
    m_write("\n",INFO);

    memory_map_t* mem;
    for(
        mem = (memory_map_t*)mboot_ptr->mmap_addr;
        (u32)mem < mboot_ptr->mmap_addr + mboot_ptr->mmap_length;
        mem = (memory_map_t*) ( (u32)mem + mem->size + sizeof(mem->size) )
      ){

      //m_write("size:",INFO);
      //m_putint( mem->size );
      m_write("b_h:",INFO);
      m_putint( mem->base_addr_high );
      m_write(" b_l:",INFO);
      m_putint( mem->base_addr_low );
      m_write(" l_h:",INFO);
      m_putint( mem->length_high );
      m_write(" l_l:",INFO);
      m_putint( mem->length_low );
      m_write(" type:",INFO);
      m_putint( mem->type );
      m_write("\n",INFO);
      //m_write("mem:",INFO);
      //m_putint( (u32)mem );
      //m_write("  after:",INFO);
      //m_putint( (u32)mem + mem->size + sizeof(mem->size) );
      //m_write("\n",INFO);

    }
}
