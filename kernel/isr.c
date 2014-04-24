#include "common.h"
#include "isr.h"
#include "monitor.h"

isr_t int_handler[256];

void register_interrupt_handler(u8 n, isr_t handler){

    int_handler[n] = handler;
}

void isr_handler( registers_t regs ){
    m_write("isr handler\n", INFO);
    m_write("int no:", INFO);
    m_putint(regs.int_no);
    m_write("error no:", INFO);
    m_putint(regs.err_code);
    m_write("\n", INFO);

    if( int_handler[regs.int_no] !=0 ){
        isr_t handler = int_handler[regs.int_no];
        handler(regs);
    }
    else
        m_write("handler have not ini\n", INFO);

}

void irq_handler( registers_t regs ){

    //m_write("irq handler\n", INFO);
    //m_write("int no:", INFO);
    //m_putint(regs.int_no);
    //m_write("\n", INFO);

    if( regs.int_no > 40 )
        out_byte(0xA0, 0x20);

    out_byte(0x20, 0x20);

    
    if( int_handler[regs.int_no] !=0 ){
        isr_t handler = int_handler[regs.int_no];
        handler(regs);
    }
    //else
    //    m_write("handler have not ini\n", INFO);
}
