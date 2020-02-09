bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fprintf, scanf, fclose, fopen              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    n resb 9
    cnt db 0
    cnt1 db 0
    message db "n=", 0
    format db "%s", 0
    rez_int dw 0
    format1 db "numarul e %d.%d ", 0
    nume_fisier db "result.txt", 0
    mod_acces db "w", 0
    
    rez1 dd 0
    rez2 dd 0
    descriptor_fis db -1
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push dword n
        push dword format
        call [scanf]
        add esp, 4*2
        mov esi, n
        
        for1:
            mov eax, 0
            
            lodsb
            cmp al, '.'
            je endi
            
            sub al, '0'
            push eax
            inc byte [cnt]
            
            jmp for1
            
        endi:
        
        mov ecx, 0
        mov cl, [cnt]
        
        mov dx, 1
        mov bx, 0
        for2:
            pop eax; eax = cifra care e pe ax
            push ecx; eliberez registrul
            
            mov cx, dx
            mul dx; inmultesc cifra cu dx si rezultatul e pe dx:ax si o sa-l retin inainte pe cx, dar fiind max 4 cifre e pe ax doar
            
            mov dx, cx
            add bx, ax; o adaug la numarul format in bx
            
            mov ax, dx; pun pe ax, dx 
            
            mov cx, 10; o sa inmultesc cu 10
            mul cx; eax = cx * dx
            
            mov dx, ax; readaug in dx = ax (adica tin puterile lui 10)
            
            pop ecx
            loop for2
            
        ; rezultatul e in bx
        add bx, 3; partea intreaga din 3.1415
        mov [rez_int], bx
        ; urmeaza sa fac pentru partea intreaga
        
        mov esi, n
        mov eax, 0
        mov al, [cnt]
        add esi, eax
        add esi, 1
        
        for3:
            mov eax, 0
            lodsb
            cmp al, 0
            je endi1
            
            sub al, '0'
            push eax
            inc byte [cnt1]
            
            jmp for3
        
            
        endi1:
        mov dx, 1
        
        mov ebx, 0
        mov ecx, 0
        mov cl, 4
        sub cl, [cnt1]
        jecxz nextu
        
        for5: 
            mov eax, 0
            push ecx; eliberez registrul
            
            mov cx, dx
            mul dx; inmultesc cifra cu dx si rezultatul e pe dx:ax si o sa-l retin inainte pe cx, dar fiind max 4 cifre e pe ax doar
            
            mov dx, cx
            add bx, ax; o adaug la numarul format in bx
            
            mov ax, dx; pun pe ax, dx 
            
            mov cx, 10; o sa inmultesc cu 10
            mul cx; eax = cx * dx
            
            mov dx, ax; readaug in dx = ax (adica tin puterile lui 10)
            
            pop ecx
            
            loop for5
        
        
        nextu:
        
        mov ecx, 0
        mov cl, [cnt1]
        
        for4:
            pop eax; eax = cifra care e pe ax
            push ecx; eliberez registrul
            
            mov cx, dx
            mul dx; inmultesc cifra cu dx si rezultatul e pe dx:ax si o sa-l retin inainte pe cx, dar fiind max 4 cifre e pe ax doar
            
            mov dx, cx
            add bx, ax; o adaug la numarul format in bx
            
            mov ax, dx; pun pe ax, dx 
            
            mov cx, 10; o sa inmultesc cu 10
            mul cx; eax = cx * dx
            
            mov dx, ax; readaug in dx = ax (adica tin puterile lui 10)
            
            pop ecx
            loop for4
        
        mov ecx, 0
        add ebx, 1415; ebx partea fractionara
        
        mov cx, [rez_int]
        
        cmp ebx, 9999
        jle aici
        add cx, 1
        sub ebx, 10000
        
        
        aici:
        
        mov dword [rez1], ebx
        mov dword [rez2], ecx
        
        push mod_acces
        push nume_fisier
        call [fopen]
        add esp, 4 * 2
        mov [descriptor_fis], eax
        
        mov ebx, [rez1]
        mov ecx, [rez2]
        push ebx
        push ecx
        push format1
        push dword [descriptor_fis]        
        call [fprintf]
        add esp, 4 * 4
        
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4 * 1
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
