bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern scanf
import scanf msvcrt.dll
extern printf
import printf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
;Read three numbers a, m and n (a: word, 0 <= m, n <= 15, m > n) from the keyboard. Isolate the bits m-n of a and display the integer represented by those bits in base 16

 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 0
    n dw 0
    m dw 0
    format db "%d", 0
    format_hex db "%x", 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword a
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword n
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword m
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov ax, [a]
        mov cl, [m]
        mov bl, 16
        sub bl, cl
        mov cl, bl
        inc cl
        shl ax, cl
        mov cl, 16
        sub cl, [m]
        sub cl, [n]
        inc cl
        shr ax, cl
        mov [a], ax
        
        push dword [a]
        push dword format_hex
        call [printf]
        add esp, 4*2
         ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
