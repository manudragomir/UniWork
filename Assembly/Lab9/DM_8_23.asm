;Sa se citeasca de la tastatura un numar hexazecimal format din 2 cifre. Sa se afiseze pe ecran acest numar in baza 10, interpretat atat ca numar fara semn cat si ca numar cu semn (pe 8 biti).

bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a   resb    1
    format    db  '%x', 0
    format1   db  'Numarul fara semn este %u', 0
    format2   db  'Numarul cu semn este %d', 0
    nr        dd 10
    
    
segment code use32 class=code
    start:
        push a
        push format
        call [scanf]
        add esp, 4 * 2
        
        mov eax, 0
        mov al, [a]
        
        push eax
        push format1
        call [printf]
        add esp, 4 * 2
        
        push nr
        call [printf]
        add esp, 4 * 1
        
        mov al, [a]
        cbw
        cwde
        
        push eax
        push format2
        call [printf]
        add esp, 4 * 2
        
        push    dword 0
        call    [exit]