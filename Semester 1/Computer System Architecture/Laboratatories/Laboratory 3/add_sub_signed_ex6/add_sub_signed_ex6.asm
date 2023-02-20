bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;c-(d+a)+(b+c)=-8-(3+1)+(4-8)=-8-4-4=-16
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 1
    b dw 4
    c dd -8
    d dq 3
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, [a]
        cbw
        cwde
        cdq             ;edx:eax = a
        mov ebx, [d]
        mov ecx, [d+4]  ; ecx:ebx = d
        add ebx, eax
        adc ecx, edx    ; ecx:ebx = (d+a)
        clc
        mov ax, [b]
        cwde            ; eax = b
        mov edx, [c]
        add eax, edx    ; eax = (b+c)
        mov edx, 0
        add ebx, eax
        adc ecx, edx    ; ecx:ebx = (d+a)+(b+c)
        clc
        mov eax, [c]
        cdq
        mov edx, 0      ; edx:eax = c
        sub eax, ebx
        sbb edx, ecx
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
