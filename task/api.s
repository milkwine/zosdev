[SECTION .text]

%macro SYSCALL 2
    global %1
    %1:
      push eax
      mov eax,%2
      int 0x80
      pop eax
      ret
%endmacro

SYSCALL puts, 0
SYSCALL gets, 1
SYSCALL clear, 2
SYSCALL backspace, 3
SYSCALL ls, 4
;global puts
;puts:
;    xchg bx,bx
;    mov eax,0
;    int 0x80
;    ret
;
;global gets
;gets:
;    xchg bx,bx
;    mov eax,1
;    int 0x80
;    ret
;
;global clear
;clear:
;    xchg bx,bx
;    mov eax,2
;    int 0x80
;    ret
;
;global backspace
;backspace:
;    xchg bx,bx
;    mov eax,3
;    int 0x80
;    ret
