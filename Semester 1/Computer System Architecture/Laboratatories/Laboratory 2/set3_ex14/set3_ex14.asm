bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;(c+d)+(a-b)+a=(3+4)+(5-2)+5=7+3+5=15
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 5
    b dw 2
    c dw 3
    d dw 4
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, 0
        add ax, [c]
        add ax, [d]
        add bx, [a]
        sub bx, [b]
        add ax, bx
        add ax, [a]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
