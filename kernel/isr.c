#include "common.h"
#include "isr.h"
#include "monitor.h"

static isr_t int_handler[256];

void register_interrupt_handler(u8 n, isr_t handler){

    int_handler[n] = handler;
}

void isr_handler( registers_t regs ){

    m_printf("isr:%d error:%d cs:%x eip:%x esp:%x \n",regs.int_no,regs.err_code,regs.cs,regs.eip,regs.esp);

    if( int_handler[regs.int_no] !=0 ){
        isr_t handler = int_handler[regs.int_no];
        handler(&regs);
    }
    //else
    //    m_write("handler have not ini\n", INFO);

}

void irq_handler( registers_t regs ){

    //m_printf("irq:%d\n",regs.int_no);

    
    if( int_handler[regs.int_no] !=0 ){
        isr_t handler = int_handler[regs.int_no];
        handler(&regs);
    }

    if( regs.int_no > 40 )
        out_byte(0xA0, 0x20);

    out_byte(0x20, 0x20);
    //else
    //    m_write("handler have not ini\n", INFO);
}
