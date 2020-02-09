bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    format  db      '%d', 0
    nr      resd    1
    max     dd      0FFFFFFFFh
    
    
    
segment code use32 class=code
    start:
    
    whilee:
        push nr
        push format
        call [scanf]
        add esp, 4 * 2
        
        mov eax, [nr]
        cmp eax, 0
        jz final
        
        cmp eax, [max]
        
        jle whilee
        
        mov [max], eax
        
        jmp whilee
        
    final:
        push dword [max]
        push format
        call [printf]
        add esp, 4 * 2
        
        push    dword 0
        call    [exit]