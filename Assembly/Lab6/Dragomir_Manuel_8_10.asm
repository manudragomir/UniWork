; Dragomir Manuel, grupa 213, 29.11.2018, problema 10, laboratorul 8
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll                         ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    n db 0
    format db "%d", 0
    cat db 0
    restu db 0
    cnt db 0
    vec db '0123456789ABCDEF'
    format1 db "%1c", 0
    x db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    push dword n
    push dword format
    call [scanf]
    add esp, 4 * 2
    
    mov al, [n]
    mov [cat], al
    
    FOR1:
        inc byte [cnt]
        mov eax, 0
        mov al, [cat]
        mov bl, 16
        
        div bl; ah = rest, al = cat
        
        mov ebx, 0
        mov bl, ah
        push ebx
        
        cmp al, 0
        je endi
        mov [cat], al
    
        jmp FOR1
    endi:
    
    FOR2:
        pop eax
        mov ebx, vec
        add ebx, eax
        mov eax, [ebx]
        push eax
        push format1
        call [printf]
        add esp, 4 * 2
        
        dec byte [cnt]
        mov al, [cnt]
        
        cmp al, 0
        je endi1
        jmp FOR2
    
    endi1:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program