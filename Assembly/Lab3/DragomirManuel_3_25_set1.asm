; ; Dragomir Manuel-Alexandru, gr. 213, 18.10.2015, tema lab3, problema 25
; (a + b + c) - (d + d) + (b + c)
; a - byte, b - word, c - double word, d - qword - Interpretare fara semn

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
    
    a db 25
    b dw 260
    c dd 260
    d dq 150
    x dw 0
    y dq 0
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov bx, [b]; bx = b
        mov cx, 0 ; cx:bx = b facut double word
        
        mov ax, [c]; 
        mov dx, [c+2]; dx:ax = c
        
        add ax, bx; 
        adc dx, cx;
        
        push dx
        push ax
        pop dword [x] ; x = b + c
        
        mov eax, [d]
        mov edx, [d+4]; edx:eax = d
        
        mov ebx, [d]
        mov ecx, [d+4]; ecx:ebx = d
        
        add eax, ebx 
        adc edx, ecx ; edx:eax = d+d
        
        mov dword[y], eax
        mov dword[y+4], edx ; y = d+d
        
        mov al, [a]; al = a
        mov ah, 0; ax = a
        
        mov bx, [b]; bx = b
        add ax, bx; ax = a + b
        
        mov dx, 0; dx:ax = a + b
        
        mov bx, [c]
        mov cx, [c+2] ; cx:bx = c
        
        add ax, bx;
        adc dx, cx; dx:ax = a+b+c
        
        push dx
        push ax
        
        pop eax ; eax = a+b+c
        
        mov edx, 0; edx:eax=a+b+c
        mov ebx, [y]
        mov ecx, [y+4]; ecx:ebx=d+d
        
        sub eax, ebx;
        sbb edx, ecx; edx:eax = (a+b+c) - (d+d)
        
        mov ebx, [x]
        mov ecx, 0; ebx:ecx = x = b+c
        
        add eax, ebx; 
        adc edx, ecx; edx:eax = (a+b+c) - (d+d) + (b+c)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
