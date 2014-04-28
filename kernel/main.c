#include "common.h"
#include "monitor.h"
#include "descriptor.h"
#include "timer.h"
#include "multiboot.h"
#include "paging.h"
#include "common.h"
#include "buddy.h"
#include "task.h"


void show_mem(multiboot_head_t *mboot_ptr);
void syscall_handler(registers_t regs);

void kernel_main(multiboot_head_t *mboot_ptr){

    ini_descriptor();
    m_clear();
    
    //show_mem(mboot_ptr);
    //inibuddy(mboot_ptr);
    //listmem();
    //ini_paging();
    m_printf("testahha:%d\n",1234);
    m_printf("testahha:%x\n",1234);
    m_write("ini paging kernel over\n", SUC);
    //iniTask();
    //ini_timer(1000);    
    //ibreak();
    //asm volatile("sti");

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
void syscall_handler(registers_t regs){
    u8* strs = (u8*)regs.eax;
    //m_write("addr:",SUC);
    //m_putint((u32)strs);
    //m_write("\n",SUC);

    m_write(strs,INFO);
}
