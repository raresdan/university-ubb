bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;A byte string S is given. 
;Obtain the string D by concatenating the elements found on the even positions of S and then the elements found on the odd positions of S.
;Example:
;S: 1, 2, 3, 4, 5, 6, 7, 8
;D: 1, 3, 5, 7, 2, 4, 6, 8

segment data use32 class=data
    ; ...
    s db 1, 2, 3, 4, 5, 6, 7, 8
    l equ $-s
    mid equ l/2
    d resb l
; our code starts here
segment code use32 class=code
    start:
        ; ...
    mov ecx, l
    xor esi, esi
    jecxz out
    repeat:
        mov edx, s  ;edx = begging of s
        mov bl, [edx + esi]; the value computed as [begging adress (s) + esi] ; esi initially 0
        ;test bl, 01h ; test if number is odd or even (if odd => ZF = 0 else if even => ZF = 1
        
        mov edx, d
        mov [edx + esi], bl ;add the odd numbers in order until the middle of the string
        dec ecx
        inc esi
        
        mov edx, s
        mov bl, [edx+esi]
        mov edx, d
        mov [edx + esi + mid-1], bl    ;we add the even positions from the middle onwards 
        inc esi
    loop repeat
    out:
    ; exit(0)
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program
