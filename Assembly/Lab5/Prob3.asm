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
    
    S2 db 5, 6, 7
    len2 equ $ - S2
    
    D resb len1 + len2 
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    mov ecx, len1
    mov esi, 0
    
    jecxz For_2
    
    For_1:
        mov al, [S1 + esi]
        mov [D + esi], al
        inc esi
    
    loop For_1
    
    mov ecx, len2
    mov edi, len2 - 1
    jecxz Sfarsit
    
    For_2:
        mov al, [S2 + edi]
        mov [D + esi], al
        dec edi
        inc esi
    
    loop For_2
    
    Sfarsit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
