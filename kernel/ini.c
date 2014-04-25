#include "syscall.h"
static void __attribute__((section(".ini"))) taska(){
    while(1){

        puts("task 1\n"); 
    }
}
