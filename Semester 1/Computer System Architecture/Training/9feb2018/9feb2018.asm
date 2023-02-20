bits 32

global start

extern printf
import printf msvcrt.dll
extern exit
import exit msvcrt.dll

segment data use32 class=data
    qword_string dq 1110111b, 100000000h, 0ABCD0002E7FCh,5
    len equ ($-qword_string)/8
    dword_string resd len
    sum dd 0
    counter dd 0
    format db "%d ",0
segment code use32 class=code
    start:
        cld
        mov esi, qword_string
        mov edi, dword_string
        mov ecx,len
        processing:
            lodsd
            lodsd
            mov dword[sum],0
            mov dword[counter],0
            mov edx,eax
            push ecx
            mov ecx,32
            clc
            digits:
                jecxz next
                dec ecx
                rcr eax, 1
                jc one
                mov dword[sum],0
                jmp digits
                one:
                    inc dword[sum]
                    cmp dword[sum],3
                    je rank
                    jmp digits
                    rank:
                       inc dword[counter]
                       cmp dword[counter],2
                       je good
                       jmp digits
                            good:
                                mov eax,edx
                                push edx
                                push dword format
                                call [printf]
                                add esp, 4*2
                                stosd                
            next:
            pop ecx
        loop processing
        push dword[0]
        call [exit]