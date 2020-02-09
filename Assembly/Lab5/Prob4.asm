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
    
    S1 db 1, 2, 3, 4
    len1 equ $ - S1
    
    S2 db 5, 6, 7, 8
    len2 equ $ - S2
    
    D resb len1

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
    mov ecx, len1
    jecxz Sfarsit
    
    mov dl, len1
    cmp dl, len2
    jne Sfarsit
    
    mov esi, 0
    For_1:
        mov al, [S1 + esi]
        mov bl, [S2 + esi]
        
        mov edx, esi
        and edx, 1       
        
        je e_par
        jne e_impar
        
        e_par:
            add al, bl
            mov [D + esi], al
            jmp ready
           
        e_impar:
            sub al, bl
            mov [D + esi], al
            jmp ready
            
        ready:
        inc esi
    loop For_1
    
    
    
    Sfarsit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
