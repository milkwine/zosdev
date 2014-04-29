#include "common.h"
#include "descriptor.h"

GDT gdt_entries[6];
GDT_PTR gdt_ptr;

IDT idt_entries[256];
IDT_PTR idt_ptr;

TSS tss;

static void ini_gdt();
static void ini_idt();
static void ini_gdt_des(u8,u32,u32,u8,u8);
static void ini_idt_des(u8,u32,u16,u8);
static void write_tss(int, u16, u32);

extern void gdt_flush( u32 );
extern void idt_flush( u32 );
extern void tss_flush( );
extern u32 stack_top;

void ini_descriptor(){
  
  ini_gdt();
  ini_idt();

}
void set_kernel_stack(u32 esp){
    tss.esp0 = esp;
}

static void ini_gdt(){

    gdt_ptr.base = (u32)gdt_entries;
    gdt_ptr.limit = sizeof( GDT ) * 6 - 1;

    ini_gdt_des(0, 0, 0, 0, 0);                // Null segment
    ini_gdt_des(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    ini_gdt_des(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    ini_gdt_des(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    ini_gdt_des(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
    write_tss(5, 0x10, (u32)&stack_top);

    gdt_flush( (u32)&gdt_ptr );
    tss_flush();

}

// Set the value of one GDT entry.
static void ini_gdt_des( u8 num, u32 base, u32 limit, u8 access, u8 gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

static void ini_idt(){
    idt_ptr.base = (u32)idt_entries;
    idt_ptr.limit = sizeof(IDT)*256 -1;

    // Remap the irq table.
    out_byte(0x20, 0x11);
    out_byte(0xA0, 0x11);
    out_byte(0x21, 0x20);
    out_byte(0xA1, 0x28);
    out_byte(0x21, 0x04);
    out_byte(0xA1, 0x02);
    out_byte(0x21, 0x01);
    out_byte(0xA1, 0x01);

    //mask open all interrupt request
    out_byte(0x21, 0x0);
    out_byte(0xA1, 0xFF);

    memset( (u8*)idt_entries, 0, sizeof(IDT)*256 );
    ini_idt_des( 0, (u32)isr0 , 0x08, 0x8E);
    ini_idt_des( 1, (u32)isr1 , 0x08, 0x8E);
    ini_idt_des( 2, (u32)isr2 , 0x08, 0x8E);
    ini_idt_des( 3, (u32)isr3 , 0x08, 0x8E);
    ini_idt_des( 4, (u32)isr4 , 0x08, 0x8E);
    ini_idt_des( 5, (u32)isr5 , 0x08, 0x8E);
    ini_idt_des( 6, (u32)isr6 , 0x08, 0x8E);
    ini_idt_des( 7, (u32)isr7 , 0x08, 0x8E);
    ini_idt_des( 8, (u32)isr8 , 0x08, 0x8E);
    ini_idt_des( 9, (u32)isr9 , 0x08, 0x8E);
    ini_idt_des(10, (u32)isr10, 0x08, 0x8E);
    ini_idt_des(11, (u32)isr11, 0x08, 0x8E);
    ini_idt_des(12, (u32)isr12, 0x08, 0x8E);
    ini_idt_des(13, (u32)isr13, 0x08, 0x8E);
    ini_idt_des(14, (u32)isr14, 0x08, 0x8E);
    ini_idt_des(15, (u32)isr15, 0x08, 0x8E);
    ini_idt_des(16, (u32)isr16, 0x08, 0x8E);
    ini_idt_des(17, (u32)isr17, 0x08, 0x8E);
    ini_idt_des(18, (u32)isr18, 0x08, 0x8E);
    ini_idt_des(19, (u32)isr19, 0x08, 0x8E);
    ini_idt_des(20, (u32)isr20, 0x08, 0x8E);
    ini_idt_des(21, (u32)isr21, 0x08, 0x8E);
    ini_idt_des(22, (u32)isr22, 0x08, 0x8E);
    ini_idt_des(23, (u32)isr23, 0x08, 0x8E);
    ini_idt_des(24, (u32)isr24, 0x08, 0x8E);
    ini_idt_des(25, (u32)isr25, 0x08, 0x8E);
    ini_idt_des(26, (u32)isr26, 0x08, 0x8E);
    ini_idt_des(27, (u32)isr27, 0x08, 0x8E);
    ini_idt_des(28, (u32)isr28, 0x08, 0x8E);
    ini_idt_des(29, (u32)isr29, 0x08, 0x8E);
    ini_idt_des(30, (u32)isr30, 0x08, 0x8E);
    ini_idt_des(31, (u32)isr31, 0x08, 0x8E);

    ini_idt_des(32, (u32)irq0, 0x08, 0x8E);
    ini_idt_des(33, (u32)irq1, 0x08, 0x8E);
    ini_idt_des(34, (u32)irq2, 0x08, 0x8E);
    ini_idt_des(35, (u32)irq3, 0x08, 0x8E);
    ini_idt_des(36, (u32)irq4, 0x08, 0x8E);
    ini_idt_des(37, (u32)irq5, 0x08, 0x8E);
    ini_idt_des(38, (u32)irq6, 0x08, 0x8E);
    ini_idt_des(39, (u32)irq7, 0x08, 0x8E);
    ini_idt_des(40, (u32)irq8, 0x08, 0x8E);
    ini_idt_des(41, (u32)irq9, 0x08, 0x8E);
    ini_idt_des(42, (u32)irq10, 0x08, 0x8E);
    ini_idt_des(43, (u32)irq11, 0x08, 0x8E);
    ini_idt_des(44, (u32)irq12, 0x08, 0x8E);
    ini_idt_des(45, (u32)irq13, 0x08, 0x8E);
    ini_idt_des(46, (u32)irq14, 0x08, 0x8E);
    ini_idt_des(47, (u32)irq15, 0x08, 0x8E);
    
    ini_idt_des(0x80, (u32)int_syscall, 0x08, 0x8E);

    idt_flush( (u32)&idt_ptr );
}

static void ini_idt_des(u8 num, u32 base, u16 sel, u8 flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags   = flags  | 0x60 ;
}

static void write_tss(int num, u16 ss0, u32 esp0){

    u32 base = (u32)&tss;
    u32 limit = base + sizeof(TSS);
    ini_gdt_des( num, base, limit, 0xE9, 0x00 );
    
    memset((u8*)&tss, 0, sizeof(TSS));

    tss.ss0 = ss0;
    tss.esp0 = esp0;

}
