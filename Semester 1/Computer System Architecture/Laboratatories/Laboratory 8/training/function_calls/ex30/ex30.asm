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

;Read numbers (in base 10) in a loop until the digit '0' is read from the keyboard. Determine and display the smallest number from those that have been read.

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    num resb 10
    format db '%d',0
    min_num dd 0

segment code use32 class=code
    start:
        mov edi, 0
        mov eax, 0
        mov dword [min_num], 1000000 ;initialize min_num to a large number
        
    read:
        push dword num
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov eax, dword [num]    ; move the read integer into eax so it can be compared to 0
        cmp eax, 0
        je print                ; if the input is 0 print the min_num
        
        cmp eax, [min_num]      ; if the input is not 0 and is smaller than the current min_num, update the value
        jl update_min
        jmp read                ; 'loop' read until the user inputs value 0
        
    update_min:
        mov dword [min_num], eax; update the min_num with the new min value
        jmp read                ; go back until the user inputs 0 
        
    print:
        push dword [min_num]
        push dword format
        call [printf]
        add esp, 4*2
        
        push dword 0
        call [exit]