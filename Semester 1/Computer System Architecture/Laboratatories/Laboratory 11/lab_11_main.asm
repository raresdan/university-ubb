bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
extern concatenate
; declare external functions needed by our program
extern exit
extern strlen
extern printf
extern scanf                ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll      ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll     ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import strlen msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    format db "%s", 0
    format_d db "%d", 0
    a resb 100
    b resb 100
    c resb 100
    la resb 10
    lb resb 10
    lc resb 10
    result resb 300
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;Read the first string
        push dword a
        push format
        call [scanf]
        add esp, 4*2
        
        ;Compute the length of the first string
        push dword a
        call [strlen]
        add esp, 4*1
        mov [la], eax
   
        ;Read the second string
        push dword b
        push format
        call [scanf]
        add esp, 4*2
        
        ;Compute the length of the second string
        push dword b
        call [strlen]
        add esp, 4*1
        mov [lb], eax
        
        ;Read the third string
        push dword c
        push format
        call [scanf]
        add esp, 4*2
        
        ;Compute the length of the third string
        push dword c
        call [strlen]
        add esp, 4*1
        mov [lc], eax
        
        push dword [lc]
        push dword [lb]
        push dword [la]
        push dword c
        push dword b
        push dword a
        push dword result
        call concatenate
        add esp, 4*7
        
        push dword result
        push dword format
        call [printf]
        add esp, 4*2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
