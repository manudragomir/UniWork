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
    
    S db 1, 4, 2, 3, 8, 4, 9, 5
    len1 equ $ - S
    min db 0FFFFh
    max db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    mov ecx, len1
    mov esi, 0
    
    For_1:
        mov edx, esi
        and edx, 1
        
        je E_par
        jne E_impar
        
        E_par:
           mov al, [S + esi]
           cmp [max], al
           jl e_mai_mare
           jmp The_End
           
           e_mai_mare:
                mov [max], al
                jmp The_End
                
        E_impar:
            mov al, [S + esi]
            cmp al, [min]
            jb e_mai_mic
            jmp The_End
            
            e_mai_mic:
                mov [min], al
                jmp The_End
             
        The_End:
        inc esi
    
    loop For_1
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
