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
;A character string is given (defined in the data segment). Read one character from the keyboard, then count the number of occurences of that character in the given string and display the character along with its number of occurences.
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    format_c db "%c", 0
    format_c2 db "%c ", 0
    format_d db "%d", 0
    string db "anaaremere"
    endl db 0
    character dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push character
        push format_c
        call [scanf]
        add esp, 4*2
        
        mov ecx, 0
        cld
        mov esi, string
        mov edi, character
        compare:
            cmp byte[esi], 0
            je final
            lodsb
            cmp al, [edi]
            je count
            jmp compare
            count:
                inc ecx
                jmp compare
    final:
        push ecx
        
        push dword [character]
        push dword format_c2
        call [printf]
        add esp, 4*2
        
        pop ecx
        push ecx
        push format_d
        call [printf]
        add esp, 4*2
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
