; Dragomir Manuel-Alexandru, gr. 213, 18.10.2015, tema lab3, problema 25
;  Interpretare fara semn
; (a*a+b+x)/(b+b)+c*c; a-word; b-byte; c-doubleword; x-qword

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
    
    a dw 25
    b db 15
    c dd 65
    x dq 105
    y dd 0
    aux dq 0
    
    ;1099

; our code starts here
segment code use32 class=code
    start:
        ; ...
     
        mov ax, [a]; ax = a
        mov bx, [a]; bx = a
        mul bx; dx:ax = a*a
        
        mov word[y], ax;
        mov word[y+2], dx; y = a*a
        
        mov eax, 0; eax = 0
        mov al, [b]; eax = b
        
        add eax, [y]; eax = y + b = a*a + b
        mov edx, 0; edx:eax = a*a + b
        
        add eax, dword[x];
        adc edx, dword[x+4]; edx:eax = a*a + b + x
        
        mov ebx, 0
        mov bl, [b]; ebx = b
        add bl, [b]; ebx = b + b
        
        div ebx; edx:eax / ebx = eax = (a*a + b + x)/(b+b)
        
        mov [y], eax; y = eax = (a*a + b + x)/(b+b)
        
        mov eax, [c]; eax = c
        mov ebx, [c]; ebx = c
        mul ebx; edx:eax = c*c
        
        mov dword[aux], eax;
        mov dword[aux+4], edx;
        
        mov eax, [y]; = eax = (a*a + b + x)/(b+b)
        mov edx, 0; edx:eax = (a*a + b + x)/(b+b)
        
        add eax, dword[aux];
        adc edx, dword[aux+4]; edx:eax = (a*a + b + x)/(b+b) + c*c
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
