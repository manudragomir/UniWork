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
    
    a dw 2
    b db -1
    c dd 4
    x dq 3
    y dd 0
    aux dq 0
    
    ; (4-1+3)/(-2) + 16= 6/(-2) = -3 + 16 = 13 = D

; our code starts here
segment code use32 class=code
    start:
        ; ...
     mov ax, [a]
     mov bx, [a]
     
     imul bx; dx:ax = a*a
     
     mov word[y], ax;
     mov word[y+2], dx; y = a*a
     
     mov al, [b];
     cbw
     cwde; eax = b;
     
     mov ebx, [y]; 
     add eax, ebx; eax = a*a + b 
     
     cdq;
     
     add eax, dword[x];
     adc edx, dword[x+4]; edx:eax = a*a + b + x
     
     mov dword[aux], eax;
     mov dword[aux+4], edx; aux = edx:eax = a*a + b + x
     
     mov al, [b]
     add al, [b]; al = b+b
     
     cbw;
     cwde; eax = b+b
     
     mov ebx, eax; ebx = b+b
     mov eax, dword[aux];
     mov edx, dword[aux+4]; edx:eax = aux = a*a + b + x
     
     idiv ebx; eax = edx:eax / ebx = (a*a + b + x)/(b+b)
     
     mov [y], eax;  y = (a*a + b + x)/(b+b)
     
     mov eax, [c];
     mov ebx, [c];
     
     imul ebx; edx:eax = eax*ebx = c*c
     
     mov dword[aux], eax;
     mov dword[aux+4], edx; aux = c*c
     
     mov eax, [y]
     cdq;
     
     add eax, dword[aux];
     adc edx, dword[aux+4]; edx:eax = rezultat
     

        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
