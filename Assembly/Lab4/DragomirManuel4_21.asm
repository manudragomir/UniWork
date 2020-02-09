; Dragomir Manuel-Alexandru, gr. 213, 25.10.2015, tema lab4, problema 21
;Se dau cuvintele A si B. Se cere dublucuvantul C:
;bitii 0-3 ai lui C coincid cu bitii 5-8 ai lui B
;bitii 4-10 ai lui C sunt invers fata de bitii 0-6 ai lui B
;bitii 11-18 ai lui C sunt 1
;bitii 19-31 ai lui C coincid cu bitii 3-15 ai lui B

bits 32 ; assembling for the 32 bits architecture

import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 1110100011010110b
    b dw 0101010001111001b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    mov eax, 0
    mov ebx, 0; aici vom calcula rezultatul 
    mov ax, [b];
    and ax, 111100000b; izolez bitii 5-8B
    mov cl, 5
    ror ax, cl; rotesc la dreapta 5 pozitii
    or ebx, eax; c(0,3) = b(5-8)
    
    mov ax, [b]
    not ax; ax = !b
    and ax, 7Fh; ax = ! b(0,6)
    mov cl, 4
    rol eax, cl; ax = !b(4,10)
    or ebx, eax; bx = rez
    
    or ebx, 7F800h; bx = bitii rezultatului 11-18 vor fi 1
    
    mov eax, 0
    mov ax, [b]
    and ax, 1111111111111000b; ax = ia bitii 3-15 ai lui B
    mov cl, 16
    rol eax, cl;
    or ebx, eax
    
    mov [c], ebx;
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
