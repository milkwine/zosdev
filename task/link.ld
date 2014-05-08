OUTPUT_FORMAT(binary)

SECTIONS
{
    . = 0x30000000;
    .text :
    {
        *(.text)
    }
    .rodata :
	{
		*(.rodata)
	}
	.data :
	{
		*(.data)
	}
}
