bits 32

global start

extern exit, fopen, fclose, fprintf, scanf

import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
        nume_fisier     resb    30
        marca_final     db      0
        text_fisier     resb    120
        marca_final1    db      0
        mod_acces       db      'w', 0
        descriptor      resd    1
        mod_string      db      '%s', 0

segment code use32 class=code
    start:
        push nume_fisier
        push mod_string
        call [scanf]
        add esp, 4 * 2
        
        push text_fisier
        push mod_string
        call [scanf]
        add esp, 4 * 2
    
        push mod_acces
        push nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je final
        mov [descriptor], eax
        
        push dword text_fisier
        push dword mod_string
        push dword [descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        push dword [descriptor]
        call [fclose]
        add esp, 4 * 1
    
    
    final:
    push    dword 0      
    call    [exit] 