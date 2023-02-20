bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern fscanf
import fscanf msvcrt.dll
extern fprintf
import fprintf msvcrt.dll
extern scanf
import scanf msvcrt.dll
extern fopen
import fopen msvcrt.dll
extern printf
import printf msvcrt.dll
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
;Se citeste de la tastatura un nume de fisier input.txt si un caracter c. Fisierul input.txt contine cuvinte separate prin spatiu. Sa se scrie in fisierul output.txt doar cuvintele in care apare caracterul c citit pe a doua pozitie (adica apare ca a doua litera din cuvant).

;input.txt: totem ochi bidon tort    c: o     output.txt: totem tort
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    input_file resb 100
    output_file db "output.txt", 0
    ;file_name resb 1000
    file_descriptor_i dd -1
    file_descriptor_o dd -1
    format_s db "%s ", 0
    format_c db "%c", 0
    chr resb 1
    access_mode_r dd "r", 0
    access_mode_w dd "w", 0
    string resb 200
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword input_file
        push dword format_s
        call [scanf]
        add esp, 4*2
        
        push dword chr
        push dword format_c
        call [scanf]
        add esp, 4*2
        
        push dword access_mode_r    
        push dword input_file
        call [fopen]
        add esp, 4*2  
        
        mov [file_descriptor_i], eax  
        
        cmp eax, 0
        jz final
        
        push dword access_mode_w    
        push dword output_file
        call [fopen]
        add esp, 4*2  
        
        mov [file_descriptor_o], eax  
        
        cmp eax, 0
        jz final
        
    read:
        push dword string
        push dword format_s
        push dword [file_descriptor_i]
        call [fscanf]
        add esp, 4*3
        
        cmp eax, -1
        je final
        
        mov esi, string
        compare:
            cmp byte[esi], 0
            je read
            lodsb
            lodsb
            cmp al, [chr]
            je write
            jmp read
            write:
                push dword string
                push dword format_s
                push dword [file_descriptor_o]
                call [fprintf]
                add esp, 4*3
                jmp read
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
