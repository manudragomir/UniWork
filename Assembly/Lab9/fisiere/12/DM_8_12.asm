bits 32 

global start

extern exit, scanf, fprintf, fopen, fclose     

import exit msvcrt.dll    
import scanf msvcrt.dll    
import fprintf msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
                       

segment data use32 class=data
        nume_fisier     db      'text.txt', 0
        descriptor      resd        1
        mod_acces       db      'w', 0
        mod_intreg      db      '%d', 0
        nr             resd         1
        

segment code use32 class=code
    start:
        
        push mod_acces
        push nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je final_program
        
        mov [descriptor], eax
        
        while1:
            push nr
            push mod_intreg
            call [scanf]
            add esp, 4 * 2
            
            mov eax, [nr]
            cmp eax, 0
            je final_program
            
            push dword [nr]
            push mod_intreg
            push dword [descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            jmp while1
        
        
        
        final_program:
        
        push    dword 0      
        call    [exit]       
