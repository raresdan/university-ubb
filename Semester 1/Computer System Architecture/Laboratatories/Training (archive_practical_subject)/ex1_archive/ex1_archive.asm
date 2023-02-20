bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern strlen
import strlen msvcrt.dll
extern fclose
import fclose msvcrt.dll
extern fprintf
import fprintf msvcrt.dll
extern fopen
import fopen msvcrt.dll
extern printf
import printf msvcrt.dll
extern scanf
import scanf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;Sa se citeasca de la tastatura un numar n, apoi sa se citeasca mai multe cuvinte, pana cand se citeste cuvantul/caracterul "#". 
;Sa se scrie intr-un fisier text toate cuvintele citite care incep si se termina cu aceeasi litera si au cel putin n litere.

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    filename dd "output.txt", 0
    access_mode dd 'w', 0
    file_descriptor dd -1
    format_d db "%d", 0
    format_s db "%s", 0
    format_s2 db "%s ", 0
    ending dd '#'
    n dd 0
    string resd 100
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;reading the number n
        push dword n
        push dword format_d
        call [scanf]
        add esp, 4*2
        
        ;opening the output file
        push dword access_mode     
        push dword filename
        call [fopen]
        add esp, 4*2               
        
        ;saving the file descriptor
        mov [file_descriptor], eax  
        
        ; check if the file was opened correctly
        cmp eax, 0
        jz final
        
    read_strings:
        ;read a new string from the keyboard
        push dword string
        push dword format_s
        call [scanf]
        add esp, 4*2
        
        ;compare if the last input string was equal to '#' so the programm can end
        mov esi, string
        mov edi, ending
        compare:
            cmpsb
            jnz process_string
            cmp byte [edi], 0   ; check for the null terminator
            je pre_final
            jmp compare
        pre_final:
            cmp byte [esi], 0   ; check for the null terminator
            je final
        process_string:
            ;verify if the length of the input string is greater than the number n
            push dword string
            call [strlen]
            add esp, 4
            cmp eax, [n]
            jl next
            
            ;check if the first and the last (the one before null) characters are equal 
            mov esi, string
            mov al, [esi]   ; saving the first character
            mov edx, esi    ; saving a copy of the string 
            mov ebx, 0      ; counting the characters
            find_null:
                ; comparing the charcaters untill we find the null terminator
                cmp byte [edx + ebx], 0 
                jne not_found
                jmp found
            not_found:
                inc ebx
                jmp find_null
            found:
                cmp al, [edx + ebx - 1] ;
                jne next 
            print_to_file:
                ; printing to the file the strings that respect both conditions
                push dword string
                push dword format_s2
                push dword [file_descriptor]
                call [fprintf]
                add esp, 4*3
        next:    
        jmp read_strings
        
        ; closing the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
    final: 
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
