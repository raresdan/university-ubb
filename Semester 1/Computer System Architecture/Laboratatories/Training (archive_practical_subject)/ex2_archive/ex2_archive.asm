bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern printf
import printf msvcrt.dll
extern scanf
import scanf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;Se citeste de la tastatura un cuvant si un numar. 
;Daca numarul este par se cere criptarea cuvantului prin adunarea la fiecare caracter a numarului 20. 
;Daca numarul este impar se cere criptarea cuvantului prin adaugarea dupa fiecare vocala a gruparii "p"+vocala.
;Se cere afisarea cuvantului criptat.

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    format_d db "%d", 0
    format_s db "%s", 0
    string resb 100
    numar dd 0
    new_string resb 150

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword numar
        push dword format_d
        call [scanf]
        add  esp, 4*2
        
        push dword string
        push dword format_s
        call [scanf]
        add  esp, 4*2
        
        mov ax, [numar]
        test ax, 1
        jnz odd_number
        jz even_number
        
        odd_number:
            mov esi, string
            mov edi, new_string
            cmp byte [esi], 0   ; check for the null terminator
            je pre_final
            loop_odd:
                lodsb ; load a character from the input string
                cmp al, 'a'
                jl next_odd
                cmp al, 'z'
                jg next_odd
                cmp al, 'a'
                je vowel
                cmp al, 'e'
                je vowel
                cmp al, 'i'
                je vowel
                cmp al, 'o'
                je vowel
                cmp al, 'u'
                je vowel
                jmp next_odd
            vowel:
                stosb ; store the vowel in the output string
                mov bl, al
                mov al, 'p'
                stosb ; store the 'p' after the vowel
                mov al, bl ; reload the current
            next_odd:
                stosb ; store the current character in the output string
                cmp byte [esi], 0   ; check for the null terminator
                jne loop_odd
                jmp pre_final
        even_number:
            mov esi, string
            mov edi, new_string
            encryption:
                lodsb
                add al, 20      ; encryption by adding 20 to each character
                stosb
                cmp byte [esi], 0   ; check for the null terminator
                je pre_final
                jmp encryption
        pre_final:
            cmp byte [edi], 0   ; check for the null terminator
            je final 
        ; exit(0)
    final:
        push new_string
        push dword format_s
        call [printf]
        add esp, 4*2
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
