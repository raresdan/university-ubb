bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions


                          
;x+a/b+c*d-b/c+e=7+16/8+4*5-8/4+9=7+2+20-2+9=29-2=27+9=36

;a,b,d-byte; c-word; e-doubleword; x-qword                         
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 16
    b db 8
    c dw 4
    d db 5 
    e dd 9 
    x dq 7
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, [a]
        mov ah, 0           ;ax=a=16
        mov bl, [b]
        div bl              ;al=a/b=2
        mov al, bl          ;bl=a/b=2
        mov bh, 0           ;bx=a/b=2
        mov cx, bx
        mov ebx, 0
        mov bx, cx          ;ebx=a/b=2
        mov dl, [d]
        mov dh, 0           ;dx=d=5
        mov ax, [c]
        mul dx              ;dx:ax=c*d=20
        push dx
        push ax
        pop eax             ;eax:c*d=20
        add eax, ebx        ;eax=a/b+c*d=22
        mov edx, 0          ;edx:eax=a/b+c*d=22
        mov ebx, [x]
        mov ecx, [x+4]      ;ecx:ebx=x=7
        add ebx, eax
        adc ecx, edx        ;ecx:ebx=x+a/b+c*d=29
        mov al, [b]
        mov ah, 0           ;ax=b=8
        mov dx, 0           ;dx:ax=b=8
        div word [c]        ;ax=b/c=2
        mov dx, ax
        mov eax, 0
        mov ax, dx          ;eax=b/c=2
        mov edx, 0          ;dx:eax=b/c=2
        sub ebx, eax
        sbb ecx, edx        ;ecx:ebx=29-2=27
        add eax, [e]
        mov edx, ecx
        mov eax, ebx        ;edx:ebx=result

        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
