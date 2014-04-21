[SECTION .text]

global out_byte
global in_byte
global ibreak
;----------------------------------
;void out_byte(u16 port,u8 byte)
;cdcel ;push 'byte' first
;----------------------------------
out_byte:
	mov al,[esp+4+4]
	mov edx,[esp+4]
	out dx,al
	nop
	nop
	ret
	
;----------------------------------
;void in_byte(u16 port)
;----------------------------------
in_byte:
	mov edx,[esp+4]
	xor eax,eax
	in al,dx
	nop
	nop
	ret

;----------------------------------
;void ibreak()
;bochs magic break
;----------------------------------
ibreak:
    xchg bx,bx
    ret
