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
    a dw 1234h, 5678h, 90h
    len_a equ $ - a
    b dw 4h, 0abcdh, 10h, 1122h
    len_b equ $ - b
    c times 7 db 0
    x db -1

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    cld; directia de parcurgere e crescatoare
    mov ecx, len_a / 2
    mov esi, a
    mov edi, c
    
    repeta:
        lodsw; ax = ds:esi
        stosb
    loop repeta
    
    mov ecx, len_b / 2
    mov esi, b
    
    repeta2:
        lodsw
        xchg al, ah
        stosb
    loop repeta2
    
    
    mov ecx, 5
    
    FOR1:
        mov esi, c
        mov edi, c
        mov dl, 1
        push ecx
        mov ecx, 6
        FOR2:
            lodsw
            dec esi
            cmp ah, al
            jg E_OK
                xchg ah, al
                mov edi, esi
                dec edi
                stosw
                dec edi
                mov dl, 0
            E_OK:
            loop FOR2
            
        cmp dl, 0
        jne Final
        
        pop ecx
        loop FOR1
        
        
     Final:
        
        
        
        
        
        
        
        
        
    
        
        
        
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
