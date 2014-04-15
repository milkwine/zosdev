#include "common.h"
#include "monitor.h"
#include "descriptor.h"
#include "timer.h"

void main(){

    ini_descriptor();
    m_clear();
    asm volatile("int $0x3");
    asm volatile("int $0x4");
    asm volatile("int $0x22");
    asm volatile("sti");
    ini_timer(1);    
}
