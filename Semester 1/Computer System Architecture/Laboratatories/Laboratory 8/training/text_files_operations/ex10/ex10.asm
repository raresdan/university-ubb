bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern fopen
import fopen msvcrt.dll
extern fgets
import fgets msvcrt.dll
extern fputs
import fputs msvcrt.dll
extern fclose
import fclose msvcrt.dll
extern scanf
import scanf msvcrt.dll
extern printf
import printf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
;Read a file name and a text from the keyboard. Create a file with that name in the current folder and write the text that has been read to file. Observations: The file name has maximum 30 characters. The text has maximum 120 characters.
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    file_name resb 30
    content resb 120
    format db "%s", 0
    access_mode db "w", 0
    file_descriptor dd 0e
    error_message db "File not opened", 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword file_name
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword access_mode
        push dword [file_name]
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        cmp eax, 0
        jz pre_final
        
        push dword content
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword [file_descriptor]
        push dword [content]
        call [fputs]
        add esp, 4*2
        
    final:
        push dword [file_descriptor]
        call [fclose]    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    pre_final:
        push error_message
        push format
        call[printf]
        add esp, 4*2
        jmp final