;Se da un sir de caractere (definit in segmentul de date). Să se citească de la tastatură un caracter, să se determine numărul de apariţii al acelui caracter în şirul dat şi să se afişeze acel caracter împreună cu numărul de apariţii al acestuia

bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    sir             db      'ANCUTAIOANAMARIAGEORGETASIMONA', 0
    len_sir         equ      $ - sir - 1
    carac           resb    1
    format_citire   db      '%c', 0   
    na              dd      0
    format_afisare  db      'Caracterul %c apare de %d ori in sir', 0
    
    
segment code use32 class=code
    start:
        push carac
        push format_citire
        call [scanf]
        
        mov bl, [carac]
        
        mov esi, sir
        mov ecx, len_sir
        
        for1:
            lodsb
            cmp al, bl
            jnz final
            inc dword [na]
            
            final:
            loop for1
        
        push dword [na]
        mov eax, 0
        mov al, [carac]
        push eax
        push format_afisare
        call [printf]
        push    dword 0
        call    [exit]