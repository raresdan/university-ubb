bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;(d-b*c+b*2)/a=(4-2*3+2*2)/5=(4-6+4)/5=2/5=0
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 5
    b db 2
    c db 3
    d dw 4
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov bl, [b]
        mov al, [c]
        mul bl
        sub [d],ax
        mov al, 2
        mul bl
        add ax, [d]
        mov bl, [a]
        div bl
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
