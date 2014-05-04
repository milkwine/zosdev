[SECTION .ini]
global puts
puts:
    xchg bx,bx
    mov eax,0
    int 0x80
    ret

global gets
gets:
    xchg bx,bx
    mov eax,1
    int 0x80
    ret

global clear
clear:
    xchg bx,bx
    mov eax,2
    int 0x80
    ret

global backspace
backspace:
    xchg bx,bx
    mov eax,3
    int 0x80
    ret
