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
    a dw 0111011101010111b
    b dw 1001101110111110b
    c dw 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov bx, 0; 
        mov ax, [b]; ax = b
        
        and ax, 1110000000000b
        mov cl, 10
        ror ax, cl
        
        or bx, ax
        or bx, 1111000b
        
        mov ax, [a];
        and ax, 11110b
        
        mov cl, 6
        rol ax, cl 
        or bx, ax
        
        and bx, 1110011111111111b
        
        mov ax, [b]
        not ax;
        
        and ax, 1110000000000b
        
        mov cl, 4
        rol ax, cl
        
        or bx, ax
        
        mov [c], bx
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
