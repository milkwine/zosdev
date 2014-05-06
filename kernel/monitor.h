#ifndef MONITOR_H
#define MONITOR_H 1

#include "common.h"

#define BLANK 0x0020|15<<8
#define INFO 0x0F00
#define WARN 0x0E00
#define SUC 0x0A00
#define FAIL 0x0C00


void m_clear();
void m_delete();
void m_split();
void m_putchar(char ch);
void m_printf(const char* format,...);
//x:0~39,y:0~11
void m_draw_up(int x,int y);
void m_clear_up();
void m_draw_down(int x,int y);
void m_clear_down();
#endif
