bits 32

global maxim
extern n

segment data use32 public data
    max resd 1

segment code use32 public code

maxim:
    mov ecx, 0
    mov cl, [n]; punem in cl nr de elemente
    
    add esp, 4
    pop eax
    
    mov esi, eax; punem adresa lui v pe esi
    lodsd; luam primul element
    mov [max], eax; il fixam ca maxim
    lodsd; luam al doilea element
    
    sub ecx, 1; semnalam ca deja am luat un element
    repeta:
        cmp eax, [max]; comparam cu maxim
        
        jle nu_e_mai_mare; daca e mai mic sarim
        mov [max], eax
        
        nu_e_mai_mare:
        lodsd
        loop repeta
    
    sub esp, 8
    pop ecx; scoatem pe ecx adresa de intoarcere
    push dword [max]; punem in eax, maximul
    push ecx; punem din nou adresa
    ret
