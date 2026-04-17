; OS-Game-Of-Life
; BOARD INIT FILE

[bits 32]                           ; PROTECTED MODE

global init_board                   ; Indicates print_board as a global function

%include "include/constants.inc"    ; Include the contants (define)


init_board:                         ; Function that initialise the board with all the cells in the state 0
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]              ; board
    mov ebx, 0                      ; row
    mov ecx, 0                      ; col

row_loop:
    cmp ebx, MAX_ROW_BOARD
    jge end

    jmp col_loop

col_loop:
    cmp ecx, MAX_COL
    jge next_row

    ; addr = base + (row * MAX_COL + col) * 4
    mov edx, ebx                    ; addr = row
    imul edx, MAX_COL               ; addr *= MAX_COL
    add edx, ecx                    ; addr += col
    shl edx, 2                      ; addr *= 4 (bit shift left)
    add edx, eax                    ; addr += base
    ; Now we have &board[row][col]
    mov dword [edx], 0              ; Put the value of board[row][col] in edx

    inc ecx

    jmp col_loop

next_row:
    inc ebx
    mov ecx, 0                      ; reset col
    jmp row_loop

end:
    pop ebp
    ret

; DEFAUCHY | 2026