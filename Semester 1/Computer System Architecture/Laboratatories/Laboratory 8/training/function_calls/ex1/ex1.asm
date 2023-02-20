bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern printf
import printf msvcrt.dll
extern scanf
import scanf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;Read two numbers a and b (in base 10) from the keyboard and calculate their product. This value will be stored in a variable called "result" (defined in the data segment).
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dd 0
    b dd 0
    result resb 200
    format db '%d',0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword a
        push dword format
        call [scanf]
        add esp, 4*2
                        
        push dword b
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov al, [a]
        mov bl, [b]
        mul bl
        
        mov [result], ax
        
        push dword [result]
        push dword format
        call [printf]
        add esp, 4*2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
