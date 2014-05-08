#ifndef SYSCALL
#define SYSCALL 1
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
void puts(u8* str);
void gets(u8* buf,int len);
void clear();
void backspace();

#endif
