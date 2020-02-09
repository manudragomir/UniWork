; Dragomir Manuel-Alexandru, gr. 213, 15.10.2015, tema lab2, problema 16
; setul 2 cu adunari + scaderi si a,b,c,d word
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
    a dw 102
    b dw 75
    c dw 98
    d dw 40

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ax, [a]; ax = a
        add ax, [b]; ax = a + b
        add ax, [b]; ax = a + b + b
        
        mov bx, [c]; bx = c
        sub bx, [d]; bx = c - d
        
        add ax, bx; ax = (a+b+b) + (c-d)
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
