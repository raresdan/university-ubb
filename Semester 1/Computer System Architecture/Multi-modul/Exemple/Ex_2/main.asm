bits 32

global start

extern afisare

extern exit
import exit msvcrt.dll

segment data use32 class=data
    
; afisarea cifrelor de la 0 la 9
segment code use32 class=code
    start:
        mov eax, 10         ; n = 10
        
        ; afisare(n)
        push eax            ; punem valoarea lui n pe stivă
        call afisare
        add esp, 4*1
    
        ; exit(0)
        push dword 0        ; push the parameter for exit onto the stack
        call [exit]         ; call exit to terminate the program
