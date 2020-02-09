bits 32 

global start, rezultat

extern exit, printf, prefix
     
import exit msvcrt.dll
import printf msvcrt.dll


segment data use32 class=data
    mod_string      db      '%s', 0
    s1          db      'yayayaboss', 0
    len1        equ     $ - s1 - 1
    s2          db      'yayaboss', 0
    len2        equ     $ - s2 - 1
    s3          db      'yaboss', 0
    len3        equ     $ - s3 - 1
    rezultat    resb    100

segment code use32 class=code       
    start:
        push dword len2
        push s3
        push dword len1
        push s1
        call prefix
        
        push rezultat
        push mod_string
        call [printf]
        add esp, 4 * 2
        
        
        
        
        
        push    dword 0    
        call    [exit]     
