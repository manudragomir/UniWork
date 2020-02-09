bits 32

; informam asamblorul ca dorim ca functia _sumaNumere sa fie disponibila altor unitati de compilare
global _sumaNumere

; linkeditorul poate folosi segmentul public de date si pentru date din afara
segment data public data use32

; codul scris in asamblare este dispus intr-un segment public, posibil a fi partajat cu alt cod extern
segment code public code use32

; int sumaNumere(int, int)
; conventie cdecl
_sumaNumere:
    ; creare cadru de stiva pentru programul apelat
    push ebp
    mov ebp, esp
    
    ; obtinem argumentele transmise pe stiva functiei sumaNumere
    ; la locatia [ebp+4] se afla adresa de return (valoarea din EIP la momentul apelului)
    ; la locatia [ebp] se afla valoarea ebp pentru apelant
    mov eax, [ebp + 8]        ; eax <- a
    
    mov ebx, [ebp + 12]        ; ebx <- b
    
    add eax, ebx            ; calculam suma
                            ; valoarea de rezulat a functiei este in eax

    ; refacem cadrul de stiva pentru programul apelant
    mov esp, ebp
    pop ebp

    ret
    ; conventie cdecl - este responsabilitatea programului apelant sa elibereze parametrii transmisi