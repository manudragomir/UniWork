; Dragomir Manuel-Alexandru, gr. 213, 01.11.2018, tema lab5, problema 25

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s1 db '+', '4', '2', 'a', '8', '4', 'X', '5'
    len1 equ $-s1
    s2 db 'a', '4', '5'
    len2 equ $-s2
    d resb (len1+len2)
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
   
    mov ecx, len1
    mov eax, 0 ; indicele pentru primul sir
    mov esi, 0 ; indicele pentru sirul pe care vreau sa-l obtin
    
   
    for1: 
        push ecx
        mov ebx, 0
        mov ecx, len2
        for2:
            mov dl, [s1+eax] ; eax e pentru primul sir
            cmp dl, [s2+ebx] ; ebx e pentru al doilea sir
            je et ; daca am gasit un duplicat, sar la finalul buclei
            inc ebx
        loop for2
        
        mov [d+esi], dl ; daca am ajuns aici, inseamna ca nu exista in sirul secund
        inc esi ; esi e pt sirul nou
        
        et:
        pop ecx
        inc eax
        
    loop for1
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
