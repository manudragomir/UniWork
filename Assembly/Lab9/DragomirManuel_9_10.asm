;; Dragomir Manuel, grupa 213, 6.12.2018, problema 10, laboratorul 9
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fprintf, scanf, fopen, fclose, printf          ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    nume_de_fisier resb 31
    text resb 121
    descriptor_file resb 20
    mod_acces db "w", 0
    format db "%s", 0
    mesaj db "Numele fisierului este: ", 0
    mesaj1 db "Textul este: ", 0
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword mesaj
        call [printf]
        add esp, 4*1
        
        push dword nume_de_fisier
        push dword format
        call [scanf]
        add esp, 4 * 2
        
        push dword mesaj1
        call [printf]
        add esp, 4*1
        
        
        push dword text
        push dword format
        call [scanf]
        add esp, 4 * 2  
        
        ; Tot citesc char-uri %c
            
        
        push dword mod_acces
        push dword nume_de_fisier
        call [fopen]
        add esp, 4 * 2
        
        mov [descriptor_file], eax
        
        cmp eax, 0
        je final
        
        push dword text
        push dword [descriptor_file]
        call [fprintf]
        add esp, 4 * 2
        
        
        push dword [descriptor_file]
        call [fclose]
        add esp, 4
        
        
    
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
