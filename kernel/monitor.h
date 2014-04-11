#ifndef MONITOR_H
#define MONITOR_H 1

#include "common.h"

#define BLANK 0x0020
#define INFO 0x0F00
#define WARN 0x0E00
#define SUC 0x0A00
#define FAIL 0x0C00


void m_clear();
void m_putc( char, u16 );
void m_write( char*, u16 );
void m_putint( u32 num );

#endif
