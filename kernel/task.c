#include "task.h"
#include "buddy.h"

Task[MAX_TASK] ready;

void iniTask(){
    memset( (u8*)ready, 0, sizeof(TASK)*MAX_TASK );
}

int addTask(u32 begin,u32 end){

    int t_num;

    for(t_num=0;t_num<MAX_TASK;t_num++){
        if(task[t_num].status == 0)
          break;
    }

    if(t_num == MAX_TASK){
        //TODO panic
        return 0;
    }
    if( (u32)( begin<<22 ) == 0){
        //begin must align 4k
        return 0;
    }
    if( (end-begin)>>12 > TASK_MAX_PAGE ){
        //to big to map
        return 0;
    }
    Task* t = &Task[t_num];
    memset((u8*)t, 0, sizeof(Task));
    u32 load = LOADPLACE;
    while(begin < end){
        t->mmap[ t->mlen ].vaddr = load;
        t->mmap[ t->mlen++ ].paddr = begin;
        load+=0x1000;
        begin+=0x1000;
    }
    t->eip = LOADPLACE;
    t->status = 1;
    return 1;
    
}
int killTask(int pid){
    task[pid].status=0;
    int i;
    for (i = 0; i < task[pid].mlen; i++) {
        k_free( task[pid].mmap[i].paddr );
    }
}
