bits 32 ; assembling for the 32 bits architecture
global _concatenate
segment data public data use32
segment code public code use32
    _concatenate:
        ; ...
        ; the stack looks like this:
        
        ; [ebp]      - ebp
        ; [ebp + 4]  - return adress
        ; [ebp + 8]  - result
        ; [ebp + 12] - a
        ; [ebp + 16] - b
        ; [ebp + 20] - c
        ; [ebp + 24] - la
        ; [ebp + 28] - lb
        ; [ebp + 32] - lc
        
        push ebp
        mov ebp,esp
        
        ;copy a in result
        mov esi, [ebp+12]    ; esi = the offset of the string a
        mov edi, [ebp+8]    ; edi = the offset of the result string
        mov ecx, [ebp+24]   ; ecx = la (length of a)
        cld
        rep movsb           ; repeats movsb ecx(la) times
        
        ;copy b next in result
        mov esi, [ebp+16]   ; esi = the offset of the string b
                            ; edi already contains the offset of the result string
        mov ecx, [ebp+28]   ; ecx = lb (length of b)
        cld
        rep movsb           ; repeats movsb ecx(lb) times
        
        ;copy c at the end of result
        mov esi, [ebp+20]   ; esi = the offset of the string c
                            ; edi already contains the offset of the result string
        mov ecx, [ebp+32]   ; ecx = lc (length of c)
        cld
        rep movsb           ; repeats movsb ecx(lc) times
        
        mov [edi], byte 0   ; each string ends with a '0' (=/n)
    
        mov esp, ebp
        pop ebp
        
        ret
   