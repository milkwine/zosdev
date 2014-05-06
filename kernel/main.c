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
#include "initrd.h"


void show_mem(multiboot_head_t *mboot_ptr);
void syscall_handler(registers_t regs);

void kernel_main(multiboot_head_t *mboot_ptr){

    ini_descriptor();
    ini_syscall();
    m_clear();
    
    ini_initrd(mboot_ptr);
    show_mem(mboot_ptr);
    ini_buddy(mboot_ptr);
    listmem();

    ls_initrd();
    cat_initrd(12);

    ibreak();
    ini_paging();

    ini_keybord();
    m_split();
    m_clear_up();
    m_clear_down();
    m_draw_up(0,0);
    m_draw_up(39,0);
    m_draw_up(39,11);
    m_draw_up(0,11);
    m_draw_down(0,0);
    m_draw_down(39,0);
    m_draw_down(39,11);
    m_draw_down(0,11);
    ini_task();
    ini_timer(1000);    
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
