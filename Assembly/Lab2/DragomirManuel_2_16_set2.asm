; Dragomir Manuel-Alexandru, gr. 213, 15.10.2015, tema lab2, problema 16
; setul 1 inmultiri impartiri i si a,b,c, - byte, d - word
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
    a db 12
    b db 16
    c db 6
    d dw 55
    x db 0
    aux db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ah, 0 ; ah =0
        mov al, [a] ; al = a
        add al, [b] ; al = a + b
        mov bl, 2 ; bl = 2
        
        div bl ; al = (a+b)/2
        
        mov [x], al ; x = (a+b)/2
        
        mov bl, 10 ; bl = 10
        
        mov ah, 0 ; ah = 0
        mov al, [a] ; al = a
        mov cl, [c] ; cl = c
        
        div cl ; al = a/c
        
        mov [aux], al; aux = a/c
        mov al, 10
        
        sub al, [aux]; al = 10 - aux = 10 - a/c
        
        mov bl, al; bl = al = 10 - a/c
        mov al, [x]; al = x = (a+b)/2
        
        add al, bl; al = al + bl = x + aux = (a+b)/2 + (10 - a/c)
        
        mov [x], al; x = (a+b)/2 + (10 - a/c)
        
        mov ah, 0; ah = 0
        mov al, [b]; al = b
        mov bl, 4; bl = 4
        
        div bl ; al = b/4
        
        mov [aux], al; aux = b/4
        
        mov al, [x]; al = (a+b)/2 + (10 - a/c)
        
        add al, [aux]; al = (a+b)/2 + (10 - a/c) + b/4
        
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
