#ifndef COMMON_H
#define COMMON_H 1
#define ENTRY_POINT 0x100000
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
void out_byte(u16 port,u8 byte);
u8 in_byte(u16 port);
void itoha(char* buf,int buf_len,int num);
void itoia(char* buf, int buf_len, int num);
void memset( u8* dst, u8 val, u32 len);
void enable_int();
void disable_int();
void ibreak();
#endif
