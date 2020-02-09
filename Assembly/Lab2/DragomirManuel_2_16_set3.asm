; Dragomir Manuel-Alexandru, gr. 213, 15.10.2015, tema lab2, problema 16
; setul 2 cu inmultiri + impartiri si a,b,c,d byte, e,f,g,h - word
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
    a db 58
    e dw 285
    f dw 225

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
       mov al, [a]; al = a
       mov bl, [a]; bl = a
       
       mul bl; ax = a * a
       
       mov bx, [e]; bx = e
       add bx, [f]; bx = e + f
       
       sub ax, bx ; ax = ax - bx = a * a - (e + f)
     
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
