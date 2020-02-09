bits 32 

global start        

extern exit, scanf, printf, mate             
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a       resd        1
    b       resd        1
    c       resd        1
    pt_a    db      'a = ', 0
    pt_b    db      'b = ', 0
    pt_c    db      'c = ', 0
    mod_intreg  db    '%d', 0

segment code use32 class=code
       
    start:
        push pt_a
        call [printf]
        add esp, 4 * 1
        
        push a
        push mod_intreg
        call [scanf]
        add esp, 4 * 2
        
        push pt_b
        call [printf]
        add esp, 4 * 1
        
        push b
        push mod_intreg
        call [scanf]
        add esp, 4 * 2
        
        push pt_c
        call [printf]
        add esp, 4 * 1
        
        push c
        push mod_intreg
        call [scanf]
        add esp, 4 * 2
        
        push dword [a]
        push dword [b]
        push dword [c]
        
        call mate
        
        push eax
        push mod_intreg
        call [printf]
        add esp, 4 * 2
        
        push    dword 0    
        call    [exit]     
