[SECTION .ini]
global puts
puts:
    xchg bx,bx
    mov eax,0
    int 0x80
    ret
