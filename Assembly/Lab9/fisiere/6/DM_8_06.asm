bits 32

global start        

extern exit, fread, fclose, fopen, printf
              
import exit msvcrt.dll   
import fread msvcrt.dll   
import fopen msvcrt.dll   
import fclose msvcrt.dll   
import printf msvcrt.dll   

segment data use32 class=data
        descriptor_fisier   resd    1
        bloc                resb    10
        nume_fisier         db      'fisier.txt', 0
        mod_acces           db      'r', 0
        mod_afisare         db      'Cifra %d apare de %d ori', 0
        maxi                dd      0
        cifra_max           dd      0
        vector_de_frecvente resd    10
        

segment code use32 class=code
    start:
        push mod_acces
        push nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je final
        mov [descriptor_fisier], eax
        
        while1:
            push dword [descriptor_fisier]
            push dword 10
            push dword 1
            push bloc
            call [fread]
            add esp, 4 * 4
            
            cmp eax, 0
            je inchide_fisier
            
            mov ecx, eax
            mov esi, bloc
            
            for1:
                mov eax, 0
                lodsb
                cmp al, '0'
                jb treci_la_loop
                
                cmp al, '9'
                ja treci_la_loop
                
                sub al, '0'
                
                mov ebx, vector_de_frecvente
                mov edx, 4
                mul edx
                add ebx, eax
                
                inc dword [ebx]
                
                treci_la_loop:
                loop for1
                
            jmp while1
            
        
        inchide_fisier:
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4 * 1
        
        mov esi, vector_de_frecvente
        mov ecx, 10

        for2:
            lodsd
            cmp eax, [maxi]
            
            jb treci_loop
            mov [maxi], eax
            mov ebx, esi
            sub ebx, vector_de_frecvente; cifra
            
            mov eax, ebx
            mov ebx, 4
            div ebx
            sub eax, 1
            
            mov [cifra_max], eax
            
            treci_loop:
            loop for2
       
        push dword [maxi]
        push dword [cifra_max]
        push mod_afisare
        call [printf]
        add esp, 4 * 2
        
        final:
        
        push    dword 0      
        call    [exit]       
