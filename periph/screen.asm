; OS-Game-Of-Life
; SCREEN FILE

[bits 32]                       ; PROTECTED MODE

global print_char               ; Indicates print_char as a global function
global print_string             ; Indicates print_string as a global function
global reset_screen             ; Indicates reset_screen as a global function
global put_cursor               ; Indicates put_cursor as a global function

%include "include/constants.inc"; Include the contants (define)

; || REGISTERS MAPPING ||
; \/                   \/
;       c => eax
;       row => ebx
;       col => ecx
;       attr => edx
;       VIDEO_MEMORY => edi
; ========================

print_char:                     ; Write a character (eax) on the screen
    push ebp
    mov ebp, esp

    push ebx
    push edi

    mov eax, [ebp + 8]          ; c
    mov ebx, [ebp + 12]         ; row
    mov ecx, [ebp + 16]         ; col
    mov edx, [ebp + 20]         ; attr

    imul ebx, MAX_COL           ; Declare the offset
    add ebx, ecx                ; 2 * (row * 80 + col)
    imul ebx, 2

    mov edi, VIDEO_MEMORY
    add edi, ebx                ; Move the c to edi

    cmp dl, 0                   ; dl is the attribut
    jne .write_char              ; If the character have an attr. go to write_char

    mov dl, WHITE_ON_BLACK      ; else put WHITE_ON_BLACK as attr.

.write_char:
    mov [edi], al               ; al is the character to print
    mov [edi + 1], dl           ; Attr.

    pop edi
    pop ebx

    mov esp, ebp
    pop ebp
    ret                         ; void

; || REGISTERS MAPPING ||
; \/                   \/
;       str => esi
;       row => ebx
;       col => ecx
;       attr => edx
; ========================
print_string:                   ; Write a string on the screen
    push ebp
    mov ebp, esp

    push ebx

    mov esi, [ebp + 8]          ; str
    mov ebx, [ebp + 12]         ; row
    mov ecx, [ebp + 16]         ; col
    mov edx, [ebp + 20]         ; attr

.loop:
    mov al, [esi]
    cmp al, 0                   ; While we are not at the end of the string
    je .end                     ; Continue printing, else stop

    push esi                    ; Save registers

    push edx                    ; Pass parameters (attr.)
    push ecx                    ; Pass parameters (col)
    push ebx                    ; Pass parameters (row)
    push eax                    ; Pass parameters (character to print)
    call print_char             ; Function call
    add esp, 16                 ; Clean stack

    pop esi                     ; All clean, esi on top of the stack

    inc esi                     ; str[i++]
    inc ecx                     ; col++

    cmp ecx, MAX_COL            ; If col < MAX_COL, continue printing
    jl .loop

    mov ecx, 0                  ; Else col = 0 & row++
    inc ebx
    jmp .loop                   ; And continue printing

.end:
    pop ebx

    mov esp, ebp
    pop ebp
    ret                         ; void

; || REGISTERS MAPPING ||
; \/                   \/
;       Total bytes on screen => ecx
;       VIDEO_MEMORY => edi
; ========================
reset_screen:                   ; Reset the screen. Black screen.
    push ebp
    mov ebp, esp

    push edi

    mov edi, VIDEO_MEMORY

    mov ecx, MAX_COL
    imul ecx, MAX_ROW
    shl ecx, 1                  ; Total bytes on screen

.loop:
    cmp ecx, 0
    je .end

    mov [edi], al
    inc edi

    dec ecx
    jmp .loop

.end:
    pop edi

    mov esp, ebp
    pop ebp
    ret                         ; void

; || REGISTERS MAPPING ||
; \/                   \/
;       Cursor adress => eax
;       row => ebx
;       col => ecx
;       color => edx
; ========================
put_cursor:                     ; Print the cursor
    push ebp
    mov ebp, esp

    push ebx

    mov eax, [ebp + 8]          ; Cursor adress (stucture cursor_t)
    mov ebx, [eax]              ; row
    mov ecx, [eax + 4]          ; col
    mov edx, [eax + 8]          ; color

    mov eax, ' '                ; Char

    push edx
    push ecx
    push ebx
    push eax
    call print_char
    add esp, 16                 ; Clean stack

    pop ebx

    mov esp, ebp
    pop ebp
    ret                         ; void

; DEFAUCHY - RIVIERE | 2026
