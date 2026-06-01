; OS-Game-Of-Life
; PRINT PROTECTED MODE FILE

[bits 32]                   ; PROTECTED MODE

print_pm:                   ; Function that print a NULL-terminated string
    pushad                  ; Copy all the registers into the stack

    mov ax, DATA_SEG
    mov ds, ax

    mov eax, ecx            ; Set eax to the number of line (current)
    imul eax, 80            ; Multiplies by the number of column
    shl eax, 1              ; Multiplies by two
    add eax, 0xb8000        ; VIDEO MEMORY (VGA)
    mov edi, eax

print_character_pm:
    mov al, [ebx]           ; Set the first character of ebx in al
    mov ah, 0x0f            ; set the attribute in ah

    cmp al, 0               ; Compare this character to 0
    je done_pm              ; If equal, exit the loop

    mov [edi], ax

    add edi, 2
    inc ebx

    jmp print_character_pm  ; Enter the loop again

done_pm:
    popad                   ; Put the register as it was previously
    ret                     ; Exit the function

; DEFAUCHY - RIVIERE | 2026
