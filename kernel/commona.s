[SECTION .text]

global out_byte
global in_byte
global ibreak
;----------------------------------
;void out_byte(u16 port,u8 byte)
;cdcel
;先压入byte，再压入port
;call后压入下一条指令的地址
;32位压入立即数都按双字算
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

ibreak:
    xchg bx,bx
    ret
