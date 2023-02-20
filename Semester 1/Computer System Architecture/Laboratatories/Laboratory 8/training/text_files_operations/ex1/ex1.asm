bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern fopen
import fopen msvcrt.dll
extern fread
import fread msvcrt.dll
extern fclose
import fclose msvcrt.dll
extern printf
import printf msvcrt.dll

extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
;A text file is given. Read the content of the file, count the number of vowels and display the result on the screen. The name of text file is defined in the data segment.
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    file_name db "input.txt",0
    access_mode db "r", 0
    file_descriptor dd 0
    len equ 500
    content times 500 db 0
    format db "%d", 0
    num_vowels dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax 

        cmp eax, 0
        jz final
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword content       
        call [fread]
        add esp, 4*4
        
        mov esi, content
    compare:
        cmp byte [esi], 0 
        je final
        lodsb
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
        jmp compare
        vowel:
            inc dword [num_vowels]
            jmp compare

    final: 
        push dword [num_vowels]
        push dword format
        call[printf]
        add esp, 4*2
        
        push dword [file_descriptor]
        call [fclose]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
