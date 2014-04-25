#ifndef TASK_H
#define TASK_H 1

#include "common.h"
#include "isr.h"

#define MAX_TASK 10
#define TASK_MAX_PAGE 10
#define LOADPLACE 0x30000000
#define LOADSTACK 0x40000000
typedef struct _Mmap {
    u32 vaddr;
    u32 paddr;
    u32 rw;
} Mmap;

typedef struct _Task {
    u8  status;     //0:ready   1:run   -1:stop
    u32 eip;
    u32 esp;  
    u32 mlen;
    Mmap mmap[TASK_MAX_PAGE];
} Task;
void iniTask();
int addTask(u32 begin,u32 end);
void switchTask(registers_t* regs);
void killTask(int pid);
#endif
