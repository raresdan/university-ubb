bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions


;(a+b)-(a+d)+(c-a)=(1+5)-(1+4)+(3-1)=6-5+2=3                        
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 1
    b dw 5
    c dd 3
    d dq 4
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, [a]         ; al = a
        mov ah, 0           ; ax = a
        add ax, [b]         ; ax = (a+b)
        mov bx, ax
        mov eax, 0
        mov ax, bx          ; eax = (a+b)
        mov edx, 0          ; edx:eax = (a+b)
        mov bl, [a]         ; bl = a
        mov bh, 0           ; bx = a
        mov cx, bx   
        mov ebx, 0
        mov bx, cx          ; ebx = a
        mov ecx, 0          ; ecx:ebx = a
        add ebx, [d]
        adc ecx, [d+4]      ; ecx:ebx = (a+d)
        sub edx, ecx
        sbb eax, ebx        ; edx:eax = (a+b)-(a+d)
        mov cl, [a]
        mov ch, 0           ;cx = a
        mov bx, cx
        mov ecx, 0
        mov cx, bx          ; ecx = a
        mov ebx, [c]
        sub ebx, ecx        ; ebx = (c-a) 
        mov ecx, 0          ; ecx:ebx = (c-a)
        add edx, ecx
        adc eax, ebx
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
