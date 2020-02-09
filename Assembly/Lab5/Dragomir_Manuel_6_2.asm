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

     s dd 12345678h, 5bcfh, 45327h, 1798dfeh, 0f112233h
     s_len equ $ - s
     c times 7 db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
     mov esi, s
     mov edi, c
     
     mov ecx, 7
     
     repeta:
        lodsd
        dec esi
        stosb
        
     loop repeta
        
     
        
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
