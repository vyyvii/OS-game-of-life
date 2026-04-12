; OS-Game-Of-Life
; PRINT REAL MODE FILE

[bits 16]                   ; REAL MODE
print_rm:                   ; Function that print a NULL-terminated string
    pusha                   ; Copy all the registers onto the stack
    jmp print_character_rm  ; Enter the loop

print_character_rm:
    mov al, [bx]            ; Puts the first character of bx in al
    cmp al, 0               ; Compare this character to 0
    je done_rm              ; If equal, exit the loop
    mov ah, 0x0e            ; Tele-type BIOS routine
    int 0x10                ; Print the character
    add bx, 1               ; Go to the next character of bx
    jmp print_character_rm  ; Enter the loop again

done_rm:
    popa                    ; Put the register as it was previously
    ret                     ; Exit the function

; DEFAUCHY, RIVIERE | 2026
