bits 32

global start

extern printf
import printf msvcrt.dll
extern exit
import exit msvcrt.dll

segment data use32 class=data
    initial_string dd 12345678h, 12785634h, 1A4D3C28h
    len equ ($-initial_string)/4
    result_string resw len
    count1s dd 0
    format db "%d", 0
segment code use32 class=code
    start:
        cld
        mov ecx, len
        mov esi, initial_string
        mov edi, result_string
        processing:
            lodsd ; we store each dword from the string into eax; increaseas esi with 4; goes to the next dword
            mov bl, ah  ; we save the high part of the low word 
            shr eax, 24 ; we shift out 24 bits so we keep only the last 8 bits which will remain in al
            mov bh, al; we save the high part of the high word
            mov ax, bx ;  now the wanted result will be into ax register
            stosw ; stores a word from ax into edi; increaseas edi with 2 (bytes); next empty position
            clc; we clear the carry flag;  we prepeare to count 1s
            push ecx
            mov ecx, 16 ; we want to loop 16 times, to check all 16 bits of the current word
            count:
                jecxz end_count
                dec ecx ; we decrese ecx after each entry in the loop
                rcr bx, 1 ; we use rotate with carry because if will save each bit into the carry flag so we could check it
                jc increase  ; if CF = 1 we increase counter
                jmp count   ; manually loop 16 times
            increase:
                inc byte [count1s]
                jmp count
            end_count:
                pop ecx       
        loop processing
        ; after this loop, result_string will have all the words respecting the given condition
            push dword [count1s]
            push dword format
            call [printf]
            add esp, 4*2
        push    dword 0      
        call    [exit]       

