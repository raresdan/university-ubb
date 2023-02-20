bits 32

global start

extern printf
import printf msvcrt.dll
extern scanf
import scanf msvcrt.dll 
extern exit
import exit msvcrt.dll

segment data use32 class=data
     dword_string resd 10
     byte_string resd 10
     n dd 0
     suma dd 0
     format_d db "%d",0
     aux dd 0
segment code use32 class=code
    start:
        push dword n
        push dword format_d
        call[scanf]
        add esp, 4*2
        mov edi, dword_string
        mov ecx, [n]
        cmp ecx, 0
        jecxz ending
        citire:
            push ecx
            push dword aux
            push dword format_d
            call[scanf]
            add esp, 4*2
            pop ecx
            mov eax, [aux]
            stosd
        loop citire
        mov esi, dword_string
        mov edi, byte_string
        mov ecx, [n]
        counting_even:
            lodsd
            mov dword [suma],0
            digits:
                cmp eax,0
                je next_number
                mov ebx,10
                div ebx
                test dl,1
                jnz next_digit
                add [suma], dl
                next_digit:
            jmp digits
            next_number:
            push dword [suma]
            push dword format_d
            call [printf]
            add esp, 4*2
            stosb 
        loop counting_even
           
        ending:
        push dword [0]
        call[exit]