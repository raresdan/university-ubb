bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;   Given the word A, obtain the integer number n represented on the bits 0-2 of A. 
;   Then obtain the word B by rotating A n positions to the right. Compute the doubleword C:
;       *the bits 8-15 of C have the value 0
;       *the bits 16-23 of C are the same as the bits of 2-9 of B
;       *the bits 24-31 of C are the same as the bits of 7-14 of A
;       *the bits 0-7 of C have the value 1

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 0111011101010111b
    n db 0
    b resw 1
    c resd 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, [a]
        mov bx, [a]         ; ebx = A
        and ax, 0000000000000111b; keeps the positions 0-2 of A
        mov [n], al              ; n=7
        mov cl, [n]
        ror bx,  cl              ; ax = B
        mov word [b], bx         ; B = 1010 1110 1110 1110 b
        
        mov ecx, 0  ; 0000 0000 0000 0000 0000 0000 0000 0000b ; Initialising the register where C is going to be computed
        mov dx, bx
        mov ebx, 0
        mov bx, dx
        
        and eax,00000000000000000000001111111100b        ; Isolate bits 2-9 of B
        mov cl, 14
        rol eax, cl                
        or ecx, eax                                      ;C = 0000 0000 1011 1011 0000 0000 0000 0000b
        
        and ebx, 00000000000000000111111110000000b       ;Isolate bits 7-14 of A
        mov cl, 17
        rol ebx, cl             
        or ecx, ebx                                      ;C =1110 1110  1011 1011 0000 0000 0000 0000b
        
        or ecx, 00000000000000000000000011111111b ;Forcing bits 0-7 to the value 1
        
        and ecx, 11111111111111110000000011111111b;Forcing bits 8-15 to the value 0 (not neccesary because the bits were initialised with 0)
          
        ;mov doubleword[c], ecx
                    
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
