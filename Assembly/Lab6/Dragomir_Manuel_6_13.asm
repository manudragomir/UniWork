; Dragomir Manuel-Alexandru, gr. 213, 21.11.2018, tema lab6, problema 13

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
    
    s   dd  12345607h, 1A2B3C15h, 13A33412h
    len_s   equ     ($ - s)/4
    d   resb    len_s
    a db -1

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    mov ecx, len_s
    mov esi, s ;sirul sursa
    mov edi, d ;sirul destinatie
    cld
    
    FOR1:
        lodsd; eax = s[i]
        mov ah, 0 ; ah = 0
        mov dl, al ; dl = al
        mov bl, 7; bl = 7
        div bl ; 
        cmp ah, 0; daca restul e 0
        jne next
            mov al, dl
            stosb; d[i] = al
        next:
           
    loop FOR1
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
