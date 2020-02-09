;Se da un numar natural negativ a (a: dword). Sa se afiseze valoarea lui in baza 10 si in baza 16, in urmatorul format: "a = <base_10> (baza 10), a = <base_16> (baza 16)"
bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a       resd    1
    format_citire  db    '%d', 0
    format_afisare  db    'a = %d(baza 10), a = %x(baza 16)', 0
    
segment code use32 class=code
    start:
        push a
        push format_citire
        call [scanf]
        add esp, 4 * 2
        
        push dword [a]
        push dword [a]
        push format_afisare
        call [printf]
        add esp, 4 * 2        
        
        push    dword 0
        call    [exit]