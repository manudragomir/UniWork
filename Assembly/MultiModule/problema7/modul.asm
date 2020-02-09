bits 32

global prefix
extern rezultat

segment code use32 class=code
    prefix:
        
        mov esi, [esp + 4]
        mov eax, [esp + 8]
        mov edi, [esp + 12]
        mov ebx, [esp + 16]
        
        call minim
        mov ecx, eax
        cld
        mov edx, 0
        
        for1:
            cmpsb
            jne finalu
            
            mov al, [edi - 1]
            mov [rezultat + edx], al
            inc edx
            loop for1
            
        finalu:
            mov byte [rezultat + edx], 0
        
        ret 16
        
    minim:
        cmp eax, ebx
        jae ok
        
        mov eax, ebx
        
        ok:
        ret