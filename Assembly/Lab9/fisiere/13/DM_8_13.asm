bits 32 

global start

extern exit, fprintf, fopen, fclose     

import exit msvcrt.dll    
import scanf msvcrt.dll    
import fprintf msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
                       

segment data use32 class=data
        nume_fisier     db      'text.txt', 0
        descriptor      resd        1
        mod_acces       db      'w', 0
        text            db    'Ana cica Are niste meris0ar3 f2in3 r$$$$u!', 0
        len             equ      $ - text - 1
        mod_caracter    db      '%c', 0
        

segment code use32 class=code
    start:
        
        push mod_acces
        push nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je final_program
        
        mov [descriptor], eax
        
        mov ecx, len
        mov esi, text
        
        while1:
            push ecx
            mov eax, 0
            
            lodsb
            cmp al, 'a'
            jb final_loop
            
            cmp al, 'z'
            ja final_loop
            
            sub al, 32
            
            final_loop:
            push eax
            push mod_caracter
            push dword [descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            pop ecx
            loop while1
        
        
        
        final_program:
        push    dword 0      
        call    [exit]       
