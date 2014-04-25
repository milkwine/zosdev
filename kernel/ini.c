#include "syscall.h"
static void __attribute__((section(".ini"))) ini(){
    char buf[] = "abcdefg\n";
    int i,j;
    while(1){
        for (i = 0; i < 7; i++) {
            buf[i]++;
        }
        puts(buf); 

        //delay
        for (i = 0; i < 10000; i++) {
            for (j = 0; j < 1000; j++) {
              /* code */
            }    
        }
        puts("====================\n");
        //delay
        for (i = 0; i < 10000; i++) {
            for (j = 0; j < 1000; j++) {
              /* code */
            }    
        }
    }
}

static void __attribute__((section(".test"))) test(){
    int i,j;
    while(1){
        char* str = "test_task.....\n";
        asm (
        "mov %0, %%eax" 
        : 
        :"r"(str)
        : "eax"
        );

        asm volatile("int $0x80");

        for (i = 0; i < 1000; i++) {
            for (j = 0; j < 1000; j++) {
              /* code */
            }    
        }

    }
}
