#ifndef TASK_H
#define TASK_H 1

#include "common.h"
#include "isr.h"

#define MAX_TASK 10
#define TASK_MAX_PAGE 10
#define LOADPLACE 0x30000000
#define LOADSTACK 0x40000000
#define KERNELSTACK 0x90000000
typedef struct _Mmap {
    u32 vaddr;
    u32 paddr;
    u32 rw;
} Mmap;

typedef struct _Task {
    u8  status;     //1:ready   2:run   -1:stop
    //
    u32 ds,edi, esi, ebp, ebx, edx, ecx, eax;
    //
    u32 eip; u32 cs; u32 eflags; u32 esp;u32 ss;
    //
    u32 k_esp;

    //memory map
    u32 mlen;
    Mmap mmap[TASK_MAX_PAGE];
} Task;
void ini_task();
int addTask(u32 begin,u32 end);
void switchTask(registers_t* regs);
void killTask(int pid);
#endif
