
print_function:             ; Function that print a NULL-terminated string
    pusha                   ; Copy all the registers onto the stack
    jmp print_character     ; Enter the loop

print_character:
    mov al, [bx]            ; Puts the first character of bx in al
    cmp al, 0               ; Compare this character to 0
    je done                 ; If equal, exit the loop
    mov ah, 0x0e            ; Tele-type BIOS routine
    int 0x10                ; Print the character
    add bx, 1               ; Go to the next character of bx
    jmp print_character     ; Enter the loop again

done:
    popa                    ; Put the register as it was previously
    ret                     ; Exit the function