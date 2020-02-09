;Se citeste de la tastatura un sir de numere in baza 10, cu semn. Sa se determine valoarea maxima din sir si sa se afiseze in fisierul max.txt (fisierul va fi creat) valoarea maxima, in baza 16.
; Dragomir Manuel, grupa 213, 14.12.2018, problema 25, laboratorul 9 multi modul

bits 32

global start
global n    

extern exit       
extern maxim
extern fprintf
extern fopen
extern scanf
      
import exit msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll

segment data use32 public class=data
    ; ...
    
    maxi resd 1
    format_hexa db '%x', 0
    format_intreg db '%d', 0
    v resd 100
    n resb 1
    var resd 1
    nume_fisier db 'max.txt', 0
    mod_acces db 'w', 0
    descriptor_fisier resd 1

segment code use32 public class=code
    start:
        push n
        push format_intreg
        call [scanf]
        add esp, 4 * 2
        
        mov ecx, 0
        mov cl, byte [n]
        
        mov edi, v
        
        citeste:
            push ecx
            push var
            push format_intreg
            call [scanf]
            add esp, 4 * 2
            pop ecx
            
            mov eax, [var]
            stosd
            loop citeste
        
        
        ; incepem functia de maxim
        
        mov eax, v; punem in eax adresa lui v
        push eax; punem pe stiva adresa lui v
        call maxim
        
        pop eax ; avem in eax rezultatul
        add esp, 4
        
        mov [maxi], eax
        
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
            
        mov [descriptor_fisier], eax
        cmp eax, 0
        je final
        
        push dword [maxi]
        push format_intreg
        push dword [descriptor_fisier]
        call [fprintf]
        add esp, 4*3
        
        final:
        push    dword 0    
        call    [exit]     
