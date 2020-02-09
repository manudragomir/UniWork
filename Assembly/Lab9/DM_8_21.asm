;Sa se citeasca de la tastatura doua numere a si b de tip word. Sa se afiseze in baza 16 numarul c de tip dword pentru care partea low este suma celor doua numere, iar partea high este diferenta celor doua numere. Exemplu: a = 574, b = 136 c = 01B602C6h
bits 32

global start        

extern exit, scanf, printf
             
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll


segment data use32 class=data
    a   resw    1
    b   resw    1
    format_citire      db   '%d%d', 0
    format_afisare     db   '%x', 0
    
segment code use32 class=code
    start:
        
        push b
        push a
        push format_citire
        call [scanf]
        add esp, 4 * 3
        
        mov ax, [a]
        mov bx, [b]
        sub ax, bx
        
        push ax
        
        mov ax, [a]      
        mov bx, [b]
        
        add ax, bx
        
        push ax
        
        push format_afisare
        call [printf]
        add esp, 4
        push    dword 0
        call    [exit]