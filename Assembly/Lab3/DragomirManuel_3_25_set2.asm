; ; Dragomir Manuel-Alexandru, gr. 213, 18.10.2015, tema lab3, problema 25
; (a + b - c) + (a + b + d) - (a + b)
; a - byte, b - word, c - double word, d - qword - Interpretare cu semn

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
    a db 5
    b dw 10
    c dd 25
    d dq 100
    x dd 0
    y dq 0
    
   ; 5A
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, [a]; al = a
        cbw; ax = a
        add ax, [b]; ax = a + b
        cwde ; eax = a + b
        
        sub eax, [c]; eax = a + b - c
        mov [x], eax; x = a + b - c
        
        mov al, [a]; al = a
        cbw ; ax = a
        add ax, [b]; ax = a + b
        cwde ; eax = a + b
        cdq; edx:eax = a + b
        
        mov ebx, dword [d]
        mov ecx, dword [d+4]; ecx:ebx = d
        
        add eax, ebx;
        adc edx, ecx; edx:eax = a + b + d
        
        mov ebx, eax;
        mov ecx, edx; : ecx:ebx = a+b+d
        
        mov eax, [x]
        cdq; edx:eax = a + b - c
        
        add eax, ebx;
        adc edx, ecx; edx:eax = (a+b-c) + (a+b+d)
        
        mov dword [y], eax
        mov dword [y+4], edx; y = (a+b-c) + (a+b+d)
        
        mov al, [a]
        cbw; ax = a
        
        add ax, [b]; ax = a + b
        
        cwde;
        cdq; edx:eax = a+b
        
        mov ebx, dword[y]
        mov ecx, dword[y+4]
        
        xchg ebx, eax
        xchg ecx, edx
        
        sub eax, ebx;
        sbb edx, ecx; edx:eax = (a+b-c) + (a+b+d) - (a+b)
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
