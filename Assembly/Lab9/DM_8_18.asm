;Sa se citeasca de la tastatura un numar in baza 10 si un numar in baza 16. Sa se afiseze in baza 10 numarul de biti 1 ai sumei celor doua numere citite. Exemplu:
;a = 32 = 0010 0000b
;b = 1Ah = 0001 1010b
;32 + 1Ah = 0011 1010b
;Se va afisa pe ecran valoarea 4.
bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a   resd    1
    b   resd    1
    cnt  dd     0
    format_citire1      db      '%d', 0
    format_citire2      db      '%x', 0
    
segment code use32 class=code
    start:
        push a
        push format_citire1
        call [scanf]
        add esp, 4 * 2
        
        push b
        push format_citire2
        call [scanf]
        add esp, 4 * 2
        
        mov eax, [a]
        mov ebx, [b]
        add eax, ebx
        
        mov ecx, 31
        
        for1:
            shr eax, 1
            jnc endi
            
            inc dword [cnt]
        
            endi:
            loop for1
        
        push dword [cnt]
        push format_citire1
        call [printf]
        add esp, 4 * 2
        push    dword 0
        call    [exit]