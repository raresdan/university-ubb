bits 32 ; assembling for the 32 bits architecture
global concatenate
segment code use32 class=code
    concatenate:
        ; ...
        ; the stack looks like this:
        
        ; [esp]      - return adress
        ; [esp + 4]  - result
        ; [esp + 8]  - a
        ; [esp + 12] - b
        ; [esp + 16] - c
        ; [esp + 20] - la
        ; [esp + 24] - lb
        ; [esp + 28] - lc
        
   
        ;copy a in result
        mov esi, [esp+8]    ; esi = the offset of the string a
        mov edi, [esp+4]    ; edi = the offset of the result string
        mov ecx, [esp+20]   ; ecx = la (length of a)
        cld
        rep movsb           ; repeats movsb ecx(la) times
        
        ;copy b next in result
        mov esi, [esp+12]   ; esi = the offset of the string b
                            ; edi already contains the offset of the result string
        mov ecx, [esp+24]   ; ecx = lb (length of b)
        cld
        rep movsb           ; repeats movsb ecx(lb) times
        
        ;copy c at the end of result
        mov esi, [esp+16]   ; esi = the offset of the string c
                            ; edi already contains the offset of the result string
        mov ecx, [esp+28]   ; ecx = lc (length of c)
        cld
        rep movsb           ; repeats movsb ecx(lc) times
        
        mov [edi], byte 0   ; each string ends with a '0' (=/n)
        
        ret
   