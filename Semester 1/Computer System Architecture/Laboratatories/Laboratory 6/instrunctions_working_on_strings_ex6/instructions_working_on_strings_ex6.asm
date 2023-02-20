bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; A word string s is given. Build the byte string d such that each element d[i] contains:
;   - the count of zeros in the word s[i], if s[i] is a negative number
;   - the count of ones in the word s[i], if s[i] is a positive number
;   Example:
;       s: -22, 145, -48, 127
;       in binary:
;       1111111111101010, 10010001, 1111111111010000, 1111111
;       d: 3, 3, 5, 7                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s dw -22, 145, -48, 127
    l equ ($-s)/2
    d times l db 0 

; our code starts here
segment code use32 class=code
    start:
        ; ...
    mov ecx, l 
    cld;
    mov esi, s
    mov edi, d
    
    repeat:
        mov bx, 0000b ; Result: number of 1s.
        mov dx, 0000b ; Result: number of 0s.
        lodsw         ; ax = [esi]; increases esi
        go_back:
            test ax, 01b
            jz zero
                inc bx
                jz one
            zero:
                inc dx
            one:
                shr ax, 01b    ; Shift the byte, least significant bit to CF.
                jnc go_back    
            
    jne cf_is_1
        mov ax, dx
        jmp skip
    cf_is_1:
        mov ax, bx
    skip:
        stosw; edi = [ax], increases edi
    
    loop repeat
           
    
       

        
    ; exit(0)
    out:
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program
