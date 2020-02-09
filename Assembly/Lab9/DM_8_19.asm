;Sa se citeasca de la tastatura un octet si un cuvant. Sa se afiseze pe ecran daca bitii octetului citit se regasesc consecutiv printre bitii cuvantului. Exemplu:
;a = 10 = 0000 1010b
;b = 256 = 0000 0001 0000 0000b
;Pe ecran se va afisa NU.
;a = 0Ah = 0000 1010b
;b = 6151h = 0110 0001 0101 0001b
;Pe ecran se va afisa DA (bitii se regasesc pe pozitiile 5-12).
bits 32

global start        

extern exit, scanf, printf
      
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a   resd    1
    b   resd    1
    format_citire      db      '%d', 0
    mesaj_af           db      'DA', 0
    mesaj_neg          db      'NU', 0
    
segment code use32 class=code
    start:
        push a
        push format_citire
        call [scanf]
        add esp, 4 * 2
        
        push b
        push format_citire
        call [scanf]
        add esp, 4 * 2
        
        mov bl, byte [a]
        mov ax, word [b]
        
        mov ecx, 7
        
        for1:
            cmp al, bl
            jz exista
            shr eax, 1
            loop for1
        
        jmp nu_exista
        
        exista:
            push mesaj_af
            call [printf]
            add esp, 4 * 1
            jmp final
        
        nu_exista:
            push mesaj_neg
            call [printf]
            add esp, 4 * 1
            
        final
        
        push    dword 0
        call    [exit]