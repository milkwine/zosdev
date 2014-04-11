#ifndef COMMON_H
#define COMMON_H 1
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
void out_byte(u16 port,u8 byte);
void in_byte(u16 port);
void itoa(char* buf,int buf_len,int num);
#endif
