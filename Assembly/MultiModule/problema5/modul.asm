bits 32

segment code use32 public code
global mate

mate:
        ; a + b - c
        mov eax, [esp + 12]; a 
        mov ebx, [esp + 8]; b
        mov ecx, [esp + 4]; c 
        
        add eax, ebx
        sub eax, ecx
                
        ret 12