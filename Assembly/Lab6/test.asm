bits 32

global start        

; (b / a * 2 + 10) * 8
extern exit, scanf, printf,
import exit msvcrt.dll 
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
    ; ...
    format_str db '%c',0
    
segment code use32 class=code
    start:
        ; ...
        
        mov eax, 66h
        
        push eax
        push format_str
        call [printf]
               
                
        push    dword 0  
        call    [exit]   
