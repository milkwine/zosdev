#ifndef SYSCALL_H
#define SYSCALL_H 1
#include "isr.h"
#define MAX_SYSCALL 100
typedef void (*syscall)(registers_t);
#endif
