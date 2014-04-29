#ifndef MONITOR_H
#define MONITOR_H 1

#include "common.h"

#define BLANK 0x0020|15<<8
#define INFO 0x0F00
#define WARN 0x0E00
#define SUC 0x0A00
#define FAIL 0x0C00


void m_clear();
void m_split();
void m_printf(const char* format,...);
#endif
