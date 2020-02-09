;Se dau doua numere naturale a si b (a, b: dword, definite in segmentul de date). Sa se calculeze suma lor si sa se afiseze in urmatorul format: "<a> + <b> = <result>"
;Exemplu: "1 + 2 = 3"
;Valorile vor fi afisate in format decimal (baza 10) cu semn.

bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a       resd    1
    b       resd    1
    result  resd    1
    format_citire  db    '%d%d', 0
    format_afisare  db    '%d + %d = %d', 0
    
    
segment code use32 class=code
    start:
        mov eax, 6
        mov ebx, -6
        add eax, ebx
        
        
        push    dword 0
        call    [exit]