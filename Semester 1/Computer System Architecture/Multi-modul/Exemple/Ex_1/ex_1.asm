bits 32

global start

; funcțiile exit() și printf() sunt definite într-o librărie externă
extern exit, printf
; funcțiile vor fi importate din libraria msvcrt.dll (DLL = Dynamic Link Library)
; și vor fi legate dinamic (Load-Time Dynamic Linking)
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    format_string db "%d", 10, 13, 0
    
; afisarea cifrelor de la 0 la 9
segment code use32 class=code
    start:
        mov ecx, 10
        xor eax, eax
    .next:
        push eax
        push ecx
        
        push eax
        push dword format_string
        call [printf]
        add esp, 4*2
        
        pop ecx
        pop eax
        inc eax
        loop .next
    
        ; exit(0)
        push dword 0        ; push the parameter for exit onto the stack
        call [exit]         ; call exit to terminate the program
