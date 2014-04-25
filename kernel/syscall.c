#include "common.h"
#include "syscall.h"

void __attribute__((section(".ini"))) puts(u8* str){
    asm (
        "mov %0, %%eax" 
        : 
        :"r"(str)
        : "eax"
        );

    asm volatile("int $0x80");
}

