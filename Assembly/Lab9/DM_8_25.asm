bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a   resd    1
    b   resd    1
    format db '%d%d', 0
    format1 db '%d < %d', 0
    format2 db '%d = %d', 0
    format3 db '%d > %d', 0
    
segment code use32 class=code
    start:
        push b
        push a
        push format
        call [scanf]
        add esp, 4 * 3
        
        mov eax, [a]
        mov ebx, [b]
        
        cmp eax, ebx
        
        jz egale
        jg mai_mare
        jl mai_mic
        
        egale:
            push ebx
            push eax
            push format2
            call [printf]
            add esp, 4 * 3
            jmp final
            
        mai_mare:
            push ebx
            push eax
            push format3
            call [printf]
            add esp, 4 * 3
            jmp final
          
        mai_mic:
            push ebx
            push eax
            push format1
            call [printf]
            add esp, 4 * 3
            jmp final
        
        
        final:
            
        
        push    dword 0
        call    [exit]