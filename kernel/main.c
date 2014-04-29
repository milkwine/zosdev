#include "common.h"
#include "monitor.h"
#include "descriptor.h"
#include "timer.h"
#include "multiboot.h"
#include "paging.h"
#include "common.h"
#include "buddy.h"
#include "task.h"
#include "keybord.h"
#include "syscall.h"


void show_mem(multiboot_head_t *mboot_ptr);
void syscall_handler(registers_t regs);

void kernel_main(multiboot_head_t *mboot_ptr){

    ini_descriptor();
    ini_syscall();
    m_clear();
    
    //show_mem(mboot_ptr);
    inibuddy(mboot_ptr);
    //listmem();
    ini_paging();
    ini_keybord();
    iniTask();
    ini_timer(1000);    
    //m_split();
    //ibreak();
    asm volatile("sti");

}
void show_mem(multiboot_head_t *mboot_ptr){
    m_printf("flag:%x  addr:%x  len:%x\n",mboot_ptr->flags,mboot_ptr->mmap_addr,mboot_ptr->mmap_length);

    memory_map_t* mem;
    for(
        mem = (memory_map_t*)mboot_ptr->mmap_addr;
        (u32)mem < mboot_ptr->mmap_addr + mboot_ptr->mmap_length;
        mem = (memory_map_t*) ( (u32)mem + mem->size + sizeof(mem->size) )
      ){
        m_printf("b_h:%x b_l:%x l_h:%x l_l:%x type:%x\n",
            mem->base_addr_high,
            mem->base_addr_low,
            mem->length_high,
            mem->length_low,
            mem->type
        );

    }
}
