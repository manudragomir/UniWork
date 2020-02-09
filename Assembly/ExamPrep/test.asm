; Sa se citeasca un fisier de la tastatura. sa se creeze un fisier
; cu acel nume pe disc. Sa se scrie in fisierul creat in ordine inversa,
; caracterele
; din numele fisierului, mai intai majuscule apoi minuscule

;EX: FIsiER
;PRINT; REIFis
bits 32

global start        

extern exit, fprintf, fopen, fclose, scanf     

import exit msvcrt.dll   
import fprintf msvcrt.dll   
import fopen msvcrt.dll   
import fclose msvcrt.dll   
import scanf msvcrt.dll   

segment data use32 class=data
        nume_fisier      resb       20
        mod_afisare      db         'w', 0
        mod_caracter     db         '%c', 0
        mod_string       db         '%s', 0
        descriptor      resd        1
        contor           db         0
    
    
segment code use32 class=code
    start:
        
        push nume_fisier
        push mod_string
        call [scanf]
        add esp, 4 * 2
        
        push mod_afisare
        push nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je final
        
        mov [descriptor], eax
        
        mov ebx, nume_fisier
        
        for1:
            cmp byte [ebx], '.'
            je gata
            inc ebx
            inc byte [contor]
            jmp for1
                    
        gata:
        
        dec ebx
        
        mov ecx, [contor]
     
        for2:
            push ecx
            cmp byte [ebx], 'A'
            jb next_el
            
            cmp byte [ebx], 'Z'
            ja next_el
            
            mov eax, 0
            mov al, [ebx]
            
            push eax
            push mod_caracter
            push dword [descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            next_el:
            dec ebx
            pop ecx
            loop for2
            
        mov ebx, nume_fisier
        
        lup:
            cmp byte [ebx], '.'
            je ready
            inc ebx
            jmp lup
                    
        ready:
        
        mov ecx, [contor]
     
        lup2:
            push ecx
            cmp byte [ebx], 'a'
            jb next_elem
            
            cmp byte [ebx], 'z'
            ja next_elem
            
            mov eax, 0
            mov al, [ebx]
            
            push eax
            push mod_caracter
            push dword [descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            next_elem:
            dec ebx
            pop ecx
            loop lup2
            
        final:
        
        push dword [descriptor]
        call [fclose]
        add esp, 4 * 1
        
        
        push    dword 0    
        call    [exit]     
