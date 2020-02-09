bits 32 

global start        

extern exit
extern scanf
extern printf
extern scanf
extern fscanf
extern fopen


import exit msvcrt.dll
import scanf msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll

segment data use32 class=data
    ; ...
    format_hex db '%x', 0
    format_int db '%d', 0
    format_car db '%c', 0
    
    descriptor_file resd 1
    nr resd 1
    mesaj db 'Nu este valid', 0
    caracter_enter dd 10
    mod_acces db 'r', 0
    format_str db '%s', 0
    string resb 17
    nume_fisier db 'fisier.txt', 0

segment code use32 class=code
    start:
    
    
    read_citire:
        push nr
        push format_hex
        call [scanf]
        add esp, 4 * 2
        
        mov eax, [nr]
        
        cmp eax, 0FFFFh; eax - FFFFh
        ja re
        
        jmp gata
        
        re:
        push mesaj
        call [printf]
      
        push caracter_enter
        push format_str
        call [printf]
        
        jmp read_citire; daca e negativ continui citirea
    
    gata:
    
    ; citim nr de la tastatura
    
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov [descriptor_file], eax
    cmp eax, 0
    je final
    
    push dword string
    push dword format_str
    push dword [descriptor_file]
    call [fscanf]
    add esp, 4 * 3
    
    mov ebx, string
    
    mov edx, [nr]; in edx am nr
    mov ecx, 16
    fah:
        shr edx, 1
        jc afisare
        jnc endi
        
        afisare:
        push ecx
        push edx
        mov al, cl
        dec al
        xlat
        
        push eax
        push format_car
        call [printf]
        
        add esp, 4 * 2
        pop edx
        pop ecx
        
        endi:
        loop fah
    
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
