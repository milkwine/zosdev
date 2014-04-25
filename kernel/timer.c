#include "common.h"
#include "monitor.h"
#include "timer.h"
#include "isr.h"
#include "task.h"

u32 tick = 0;
static void timer_callback(registers_t* regs){
    //m_write("tick:",INFO);
    //m_putint(tick);
    //m_write("\n",INFO);
    tick++;
    switchTask(regs);
}

void ini_timer(u32 frequency){
       // Firstly, register our timer callback.
   register_interrupt_handler(IRQ0, &timer_callback);

   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   u32 divisor = 1193180 / frequency;

   // Send the command byte.
   out_byte(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   u8 l = (u8)(divisor & 0xFF);
   u8 h = (u8)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   out_byte(0x40, l);
   out_byte(0x40, h);
}
