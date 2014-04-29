#include "syscall.h"
#include "common.h"
static syscall calls[MAX_SYSCALL];
static void syscall0(registers_t regs);
void ini_syscall(){
    memset((u8*)calls, 0, sizeof(syscall)*MAX_SYSCALL);
    calls[0] = &syscall0;
}
void syscall_handler(registers_t regs){
    int no = (int)regs.eax;
    if(no>=0 && no<MAX_SYSCALL && (int)calls[no]!=0){
        syscall call = calls[no];
        call(regs);
    }
}
static void syscall0(registers_t regs){
    u32 addr = *(u32*)(regs.useresp+4); 
    m_printf("%s",(char*)addr);
}
