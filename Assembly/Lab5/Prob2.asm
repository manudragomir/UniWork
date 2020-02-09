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
    S db '+', '4', '2', 'a', '@', '3', '$', '*'
    len1 equ $ - S
    
    P db '!', '@', '#', '$', '%', '^', '&', '*'
    len2 equ $ - P
    
    D resb len1
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    mov ecx, len1
    mov edi, 0 ; indice sir nou
    mov esi, 0 ; indice de parcurgere a sirului S
    
    For_1:
        mov al, [S + esi]
        push ecx
        mov ecx, len2
        mov edx, 0
        
        For_2:
            mov bl, [P + edx]
            cmp al, bl
            
            jne nu_se_regaseste
                mov [D + edi], bl
                inc edi
                
            nu_se_regaseste:
                inc edx
            
        loop For_2
        
    pop ecx  
    inc esi
    loop For_1
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
