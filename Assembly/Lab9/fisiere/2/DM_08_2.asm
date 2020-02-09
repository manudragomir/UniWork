bits 32

global start        

extern exit, fread, printf, fopen, fclose     

import exit msvcrt.dll   
import fread msvcrt.dll   
import printf msvcrt.dll   
import fopen msvcrt.dll   
import fclose msvcrt.dll   

segment data use32 class=data
    descriptor_fisier   resd    1
    nume_fisier          db      'vocale.txt', 0
    mod_acces            db      'r', 0
    bloc                resb        100
    nr_consoane            dd     0
    format_afisare       db      '%d', 0
    string_vocale        db      'aeiou', 0
    

segment code use32 class=code
    start:
    ;deschidem fisierul
        push mod_acces
        push nume_fisier
        call [fopen]
        add esp, 4 * 2
        
    ;ne intrebam daca s-a deschis cu succes si salvam descriptor_fisier daca da
        cmp eax, 0
        je final_program
        
        mov [descriptor_fisier], eax
        
    ;citim cate un bloc de 100 de litere
        
    while1:
        push dword [descriptor_fisier]
        push dword 100
        push dword 1
        push bloc
        call [fread]
        add esp, 4 * 4
        
        mov ecx, eax
        jecxz afisare
        mov esi, bloc
        cld
        
        for2:
            lodsb; in al vom avea caracterul curent
            
            mov edi, string_vocale; punem in destinatie strigul de vocale
            
            push ecx
            mov ecx, 5
            
            cmp al, 'a'
            jb endi
            
            cmp al, 'z'
            ja endi
            for3:
                scasb
                
                jnz reexecuta
                jmp am_gasit
                
                reexecuta:
                loop for3
            
            inc dword [nr_consoane]
            am_gasit:
            endi:
            pop ecx
            loop for2
        
        
        cmp eax, 100
        jb afisare
        
        jmp while1
        
    
    ;functia de afisare
    afisare:
        push dword [nr_consoane]
        push format_afisare
        call [printf]
        add esp, 4 * 2
        
    ;inchidem fisierul
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4 * 1
    
    
        final_program:
    
        
        push    dword 0      
        call    [exit]       
