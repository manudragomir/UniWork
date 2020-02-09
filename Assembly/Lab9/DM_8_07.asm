;Se dau doua numere natural a si b (a: dword, b: word, definite in segmentul de date). Sa se calculeze a/b si sa se afiseze restul impartirii in urmatorul format: "<a> mod <b> = <rest>"
;Exemplu: pentru a = 23 si b = 5 se va afisa: "23 mod 5 = 3"
;Valorile vor fi afisate in format decimal (baza 10) cu semn.

bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a       resd    1
    b       resw    1
    result  resd    1
    format_citire  db    '%d%d', 0
    format_afisare  db    '%d mod %d = %d', 0
    
    
segment code use32 class=code
    start:
        push b
        push a
        push format_citire
        call [scanf]
        add esp, 4 * 3
        
        mov ax, [b]
        cwde
        mov ebx, eax
        
        mov eax, [a]
        cdq; edx:eax / ebx = 
        
        idiv ebx
        
        mov [result], edx
        
        mov bx, [b]
        test bx, 8000h
        
        mov bx, 0
        
        jz here
        mov bx, 0FFFFh
        
        here:
        
        push dword [result]
        push word bx
        push word [b]
        push dword [a]
        push format_afisare
        call [printf]
        add esp, 4 * 4
        
        
        push    dword 0
        call    [exit]