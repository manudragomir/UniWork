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
    
    a db 7
    x dq 11111111FFFFFFFFh
; our code starts here
segment code use32 class=code
    start:
        ; ...
       
       mov eax, dword[x]
       mov edx, dword[x+4]
       
       add eax, 1
       adc edx, 0 ; rez = 1111111200000000h -> rezultat corect
       
       ; add eax, 1 ; rez = 1111111100000000 -> rezultat incorect
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
