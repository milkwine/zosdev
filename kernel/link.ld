ENTRY(_start)

SECTIONS
{

    /*0x100000 */
	. = 1M;

	.text BLOCK(4K) : 
	{
		*(.multiboot)
		*(.text)
	}
	.rodata BLOCK(4K) :
	{
		*(.rodata)
	}
	.data BLOCK(4K) :
	{
		*(.data)
	}
	.bss BLOCK(4K) :
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	.page BLOCK(4K) :
    {
        *(.pagedir)
    }
    
    /*initrd loaded in 0x11F000 ~ 0xAF7000 not very sured*/

    kernel_end = 0xB00000;  /*  */

    /*0xB00000~0xF00000 used by kernel heap*/

    mem_start = 0xF00000;

}
