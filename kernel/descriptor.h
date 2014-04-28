#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H 1

void ini_descriptor();
void set_kernel_stack(u32);

typedef struct _GDT {        // 8 bytes

    u16 limit_low;           // The lower 16 bits of the limit.
    u16 base_low;            // The lower 16 bits of the base.
    u8  base_middle;         // The next 8 bits of the base.
    u8  access;              // Access flags, determine what ring this segment can be used in.
    u8  granularity;
    u8  base_high;           // The last 8 bits of the base.

}__attribute__((packed)) GDT;

typedef struct _GDT_PTR {

    u16 limit;               // The upper 16 bits of all selector limits.
    u32 base;                // The address of the first gdt_entry_t struct.

}__attribute__((packed)) GDT_PTR;

typedef struct _IDT {

    u16 base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
    u16 sel;                 // Kernel segment selector.
    u8  always0;             // This must always be zero.
    u8  flags;               // More flags. See documentation.
    u16 base_hi;             // The upper 16 bits of the address to jump to.

}__attribute__((packed)) IDT;

typedef struct _IDT_PTR {

    u16 limit;
    u32 base;                // The address of the first element in our idt_entry_t array.

}__attribute__((packed)) IDT_PTR;

struct tss_entry_struct
{
   u32 prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
   u32 esp0;       // The stack pointer to load when we change to kernel mode.
   u32 ss0;        // The stack segment to load when we change to kernel mode.
   u32 esp1;       // everything below here is unusued now.. 
   u32 ss1;
   u32 esp2;
   u32 ss2;
   u32 cr3;
   u32 eip;
   u32 eflags;
   u32 eax;
   u32 ecx;
   u32 edx;
   u32 ebx;
   u32 esp;
   u32 ebp;
   u32 esi;
   u32 edi;
   u32 es;         
   u32 cs;        
   u32 ss;        
   u32 ds;        
   u32 fs;       
   u32 gs;         
   u32 ldt;      
   u16 trap;
   u16 iomap_base;
}__attribute__((packed)) ;
 
typedef struct tss_entry_struct TSS;

// These extern directives let us access the addresses of our ASM ISR handlers.
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();


extern void int_syscall();//syscall

extern void irq0 (); 
extern void irq1 (); 
extern void irq2 (); 
extern void irq3 (); 
extern void irq4 (); 
extern void irq5 (); 
extern void irq6 (); 
extern void irq7 (); 
extern void irq8 (); 
extern void irq9 (); 
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif
