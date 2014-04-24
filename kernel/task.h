#ifndef TASK_H
#define TASK_H 1
#include "common.h"
#define MAX_TASK 10
#define TASK_MAX_PAGE 10
#define LOADPLACE 0x30000
typedef struct _Mmap {
    u32 vaddr;
    u32 paddr;
} Mmap;

typedef struct _Task {
    u8  status;     //0:ready   1:run   -1:stop
    u32 eip;
    u32 esp;  
    u32 mlen;
    Mmap[TASK_MAX_PAGE] mmap;
} Task;

void iniTask();
int addTask(u32 begin,u32 end);
void killTask(int pid);
#endif
