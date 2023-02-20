bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern printf
import printf msvcrt.dll
                          
;Two natural numbers a and b (a: dword, b: dword, defined in the data segment) are given. Calculate a/b and display the quotient in the following format: "<a>/<b> = <quotient>". Example: for a = 200, b = 5 it will display: "200/5 = 40".
;The values will be displayed in decimal format (base 10) with sign.

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    format1 db "%d ", 0
    format2 db "%c ", 0
    a dd 200d
    b dd 5d
    c dd '/'
    d dd '='
; our code starts here
segment code use32 class=code
    start:
        ; ...
    push dword [a]
    push dword format1
    call [printf]
    add esp, 4*2
    
    push dword [c]
    push dword format2
    call [printf]
    add esp, 4*2
    
    push dword [b]
    push dword format1
    call [printf]
    add esp, 4*2
    
    push dword [d]
    push dword format2
    call [printf]
    add esp, 4*2
    
    mov eax, [a]
    div dword [b] ; ax = a/b
    
    push eax
    push dword format1
    call [printf]
    add esp, 4*2
   
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
