bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
; tell nasm that exit exists even if we won't be defining it
; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;A text file is given. Read the content of the file, determine the digit with the highest frequency and display the digit along with its frequency on the screen. The name of text file is defined in the data segment.

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    file_name db "input.txt", 0 ; filename to be read
    access_mode db "r", 0       ; file access mode: r - opens a file for reading. The file must exist.
    file_descriptor dd -1       ; variable to hold the file descriptor
    len equ 100                 ; maximum number of characters to read
    format db "The number is: %d. The frequency is: %d", 0  ;Printing format
    input_text times 100 db 0   ;The text read from the file
    frecv times 10 db 0         ;Frequency 'array'
    max_frecv dd 0
    max_nr dd 0

; our code starts here
segment code use32 class=code
    start:
        
        ; call fopen() to open the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen

        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        jz final

        ; read the text from file using fread()
        ; eax = fread(text, 1, len, file_descriptor)
        repeat_reading:
            push dword [file_descriptor]
            push dword len
            push dword 1
            push dword input_text       
            call [fread]
            add esp, 4*4
        
        
            ; determine the digit with the highest frequency
            ; when the program stops reading, jump at the end           
            cmp EAX, 0
            je end_of_reading
       
            ; parsing the frequency 'array'
        
            mov EBX, 0
            mov ESI, input_text
            mov EDI, frecv
            mov ECX, EAX
        
            for_every_character:
            ; comparing the character, so it is a digit between 0 and 9
                find_the_frequency:
                    mov EAX, 0
                    lodsb
                    cmp AL, '0'
                    jb not_digit
                    cmp AL, '9'
                    jg not_digit
            ; finding the digit by subtracting ascii code of '0' and increasing it's frequency       
                    sub AL, '0'
                    inc byte[EDI + EAX] 
        
        ; go back until we have character left to check or numbers left to be read      
        not_digit:
            loop for_every_character
            jmp repeat_reading
               
    end_of_reading:    
    ; call fclose() to close the file
    ; fclose(file_descriptor)
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    ; determine the highest frequency
    mov ESI, frecv
    mov EBX, 0
    mov ECX, 0
    find_maximum_frequency:
        lodsb
        cmp AL, [max_frecv]
        jb not_found_larger
        mov [max_frecv], AL
        mov [max_nr], ECX
        
    not_found_larger:
        inc ECX
        cmp ECX, 10
        jne find_maximum_frequency
        
        
    ; printf(format, number, frequency)
    push dword [max_frecv]
    push dword[max_nr]
    push dword format
    call [printf]
    add esp, 4*3

    final:

    ; exit(0)
    push dword 0
    call [exit]