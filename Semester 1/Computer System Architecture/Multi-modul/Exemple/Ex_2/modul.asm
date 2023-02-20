bits 32

global afisare

; funcția este definită într-o librărie externă
extern printf
; functia printf() va fi importata din libraria msvcrt.dll (DLL = Dynamic Link Library)
; și va fi legată dinamic (Load-Time Dynamic Linking)
import printf msvcrt.dll

segment data use32 class=data
    format_string db "%d", 10, 13, 0

segment code use32 class=code
; afisare(n)
; intrare: valoarea lui n este pe stiva
; iesire: procedura afiseaza pe ecran cifrele de la 0 la n-1
afisare:
    mov ecx, [esp+4]            ; valoarea lui n
    xor eax, eax
    .next:
        push eax
        push ecx
        
        push eax
        push dword format_string
        call [printf]           ; numele funcției este cuprins între paranteze pătrate
        add esp, 4*2
        
        pop ecx
        pop eax
        inc eax
    loop .next
    
    ret
