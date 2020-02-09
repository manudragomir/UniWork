bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fread, fopen, fclose, scanf, printf, fscanf            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll  
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fscanf msvcrt.dll  ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    nume_fisier db "fisier.txt", 0
    format_int db "%d", 0
    format_string db "%s", 0
    format_caracter db "%c", 0
    mod_acces db "r", 0
    n resd 1
    nr resd 1
    len equ 5
    x resd 1
    descriptor_file resb 10

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        mov [descriptor_file], eax
        cmp eax, 0
        je final
        
        push dword n
        push dword format_int
        push dword [descriptor_file]
        call [fscanf]
        add esp, 4*3
       
        mov eax, [n]
        
        loop1:
            push dword x
            push dword format_int
            call [scanf]
            add esp, 4 * 2
            
            mov eax, [x]
            cmp eax, 0
            
            jl final
            
            mov eax, [n]
            cmp eax, [x]
            jle loop1
            
            
            ;incepem citirea linie cu linie
            ;deschidem fisierul
            
            push dword mod_acces
            push dword nume_fisier
            call [fopen]
            add esp, 4 * 2
            
            mov [descriptor_file], eax
            cmp eax, 0
            je final
            
            ; am deschis fisierul iar acum numaram sa fie x endline-uri citind litera cu litera din fisier
            
            mov ebx, [x]; in ebx avem nr de endline-uri
            add ebx, 1
            looop:
                push dword [descriptor_file]
                push dword 1
                push dword 1
                push nr
                call [fread]
                add esp, 4*4
                
                mov eax, [nr]
                cmp eax, 10
                
                jne endul
                
                sub ebx, 1
                
                cmp ebx, 0
                je afisare
                
                
                endul
                jmp looop
            
                ; aici vom incepe afisarea liniei cu pricina
            afisare:    
                push dword [descriptor_file]
                push dword 1
                push dword 1
                push nr
                call [fread]
                add esp, 4*4
                
                push dword [nr]
                push format_caracter
                call [printf]
                add esp, 4 * 2
                
                mov eax, [nr]
                cmp eax, 10
                
                je finl
                jmp afisare
            
            
            finl:
            ;inchidem fisierul
            push dword [descriptor_file]
            call [fclose]
            
            
            jmp loop1
        
        
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
