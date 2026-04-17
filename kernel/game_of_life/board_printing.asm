; OS-Game-Of-Life
; BOARD PRINTING FILE

[bits 32]                           ; PROTECTED MODE

global print_board                  ; Indicates print_board as a global function
global print_cell                   ; Indicates print_cell as a global function
[extern print_char]                 ; Indicates print_char as an extern function

%include "include/constants.inc"    ; Include the contants (define)

print_board:                        ; Function that print the board
    ; NOTE: VGA text mode is 25 by 80 cells large, but here, the first line is infos.
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]              ; Board
    mov ebx, 1                      ; row

row_loop:                           ; Handle cell calling in each row & ending
    cmp ebx, MAX_ROW                ; While row < MAX_ROW
    jge end                         ; Continue, else end

    mov ecx, 0                      ; col

col_loop:                           ; Handle cell management and incrementation
    cmp ecx, MAX_COL                ; While col < MAX_COL
    jge next_row                    ; Continue, else go to next_row

    push eax                        ; Save register (board)
    push ebx                        ; Save register (row)
    push ecx                        ; Save register (col)

    push ecx                        ; Pass parameters (col)
    push ebx                        ; Pass parameters (row)
    push eax                        ; Pass parameters (board)
    call print_cell                 ; Function call
    add esp, 12                     ; Clean stack

    pop ecx                         ; Get saved register (col)
    pop ebx                         ; Get saved register (row)
    pop eax                         ; Get saved register (board)

    inc ecx                         ; col++
    jmp col_loop                    ; Continue

next_row:
    inc ebx                         ; row++
    jmp row_loop                    ; Continue with an other row

end:                                ; End the function
    pop ebp
    ret

print_cell:                         ; Function that print a cell of the board
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]              ; board
    mov ebx, [ebp + 12]             ; row
    mov ecx, [ebp + 16]             ; col

    ; addr = base + (row * MAX_COL + col) * 4
    mov edx, ebx                    ; addr = row
    imul edx, MAX_COL               ; addr *= MAX_COL
    add edx, ecx                    ; addr += col
    shl edx, 2                      ; addr *= 4 (bit shift left)
    add edx, eax                    ; addr += base
    ; Now we have &board[row][col]
    mov edx, [edx]                  ; Put the value of board[row][col] in edx

    cmp edx, 1                      ; If board[row][col] != 1
    jne .null                       ; go to null
    ; else continue

    mov eax, ' '                    ; character
    mov edx, BLACK_ON_WHITE         ; attr.

    jmp .continue

.null:
    mov eax, ' '                    ; character
    mov edx, WHITE_ON_BLACK         ; attr.

.continue:
    push edx                        ; attr.
    push ecx                        ; col
    push ebx                        ; row
    push eax                        ; character to print
    call print_char                 ; Function call
    add esp, 16                     ; Clean stack

.end:
    pop ebp
    ret

; DEFAUCHY | 2026
