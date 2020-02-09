bits 32 

global start

extern exit, printf, scanf
     
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
        primul_sir      resb       20
        sir_suport      resb       20
        mod_string       db        '%s', 0
        true             db         0
        mesaj            db         'Am gasit', 0
        

segment code use32 class=code 
    subsecventa:
        mov edi, [esp + 4]; sir suport
        mov esi, [esp + 8]; primul sir
        
        mov ebx, esi
        call lungime
        mov edx, ecx
        
        ; in edx am lungimea sirului esi
        
        mov ebx, edi
        call lungime
        
        ; in ecx am lungimea sirului edi
        
        mov eax, 0; indice pentru esi
        mov ebx, 0; indice pentru edi
        mov byte [true], 0
        
        for1:
            mov ebx, 0
            for2:
                push ecx
                mov ecx, [edi+ebx]
                cmp ecx, [esi+eax]
                pop ecx
                jne gatafor2
                
                inc ebx
                inc eax
                
                cmp ebx, edx
                je am_gasit
                jne mai_incerc
                
                am_gasit:
                mov byte [true], 1
                jmp redi
                
                mai_incerc:
                cmp eax, ecx
                jne for2
                
            gatafor2:
            inc eax
            sub eax, ebx
            cmp eax, ecx; i == n
            jne for1; 
        
        redi:
        ret 8
        
    lungime:
        ;in ebx am un sir
        mov ecx, 0
        mov al, 0
        
        foru:
            cmp byte [ebx + ecx], 0
            je gata
            
            inc ecx
            jmp foru
        
        gata:
        ret
        
    start:
        push primul_sir
        push mod_string
        call [scanf]
        add esp, 4 * 2
        
        while_citire:
            push sir_suport
            push mod_string
            call [scanf]
            add esp, 4 * 2
            
            cmp byte [sir_suport], '0'
            je final
            
            push primul_sir
            push sir_suport
            call subsecventa
            
            cmp byte [true], 1
            jne continua
            
            push mesaj
            push mod_string
            call [printf]
            
            continua:
            jmp while_citire
            
            
        final:
        
        
        
        push    dword 0    
        call    [exit]     
