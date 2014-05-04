#include "syscall.h"
#include "common.h"
#include "keybord.h"
#include "monitor.h"
static syscall calls[MAX_SYSCALL];
static void syscall0(registers_t regs);     //puts
static void syscall1(registers_t regs);     //gets
static void syscall2(registers_t regs);     //clear
static void syscall3(registers_t regs);     //backspace

void ini_syscall(){
    memset((u8*)calls, 0, sizeof(syscall)*MAX_SYSCALL);
    calls[0] = &syscall0;
    calls[1] = &syscall1;
    calls[2] = &syscall2;
    calls[3] = &syscall3;
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

static void syscall1(registers_t regs){
    u32 addr = *(u32*)(regs.useresp+4); 
    u8* buf = (u8*)addr;
    int len = *(int*)(regs.useresp+8);
    keybord_read(buf,len);
}
static void syscall2(registers_t regs){
    m_clear();
}
static void syscall3(registers_t regs){
    m_delete();
}
