;Sa se citeasca de la tastatura in baza 16 doua numere a si b de tip dword si sa se afiseze suma partilor low si diferenta partilor high. Exemplu:
;a = 00101A35h, b = 00023219h
;suma = 4C4Eh
;diferenta = Eh
bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a     resd    1
    b     resd    1
    rez1  resd    1
    rez2  resd    1
    format_citire    db    '%x%x', 0
    format_afisare1  db    'suma = %x', 0
    enteri           dd    10
    format_afisare2  db    'diferenta = %x', 0
    
segment code use32 class=code
    start:
        push b
        push a
        push format_citire
        call [scanf]
        add esp, 4 * 3
        
        mov eax, 0
        mov ebx, 0
        
        mov bx, [b]
        mov ax, [a]
        
        add ax, bx
        mov [rez1], eax
        
        mov bx, [b+2]
        mov ax, [a+2]
        
        sub ax, bx
        mov [rez2], eax
        
        
        push dword [rez1]
        push format_afisare1
        call [printf]
        add esp, 4 * 2        
        
        push enteri
        call [printf]
        add esp, 4 * 1 
        
        push dword [rez2]
        push format_afisare2
        call [printf]
        add esp, 4 * 2        
        
        push    dword 0
        call    [exit]