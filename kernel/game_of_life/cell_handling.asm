; OS-Game-Of-Life
; BOARD PRINTING FILE WIP

[bits 32]                           ; PROTECTED MODE

global generation                   ; Indicates generation as a global function
[extern print_char]                 ; Indicates print_char as an extern function

%include "include/constants.inc"    ; Include the contants (define)

generation:                         ; Function that play a generation of the GoL
    push ebp
    mov ebp, esp

    mov eax, [epb + 8]              ; board
    mov ebx, 0                      ; row
    mov ecx, 0                      ; col

row_loop:
    cmp ebx, MAX_ROW
    je end

col_loop:
    cmp ecx, MAX_COL
    je next_row

    push eax
    push ebx
    push ecx

    push ecx                        ; col
    push ebx                        ; row
    push eax                        ; board
    call simul_one_cell             ; Function call
    add esp, 12                     ; Clean stack

    pop ecx
    pop ebx
    pop eax

    inc ecx
    jmp col_loop

next_row:
    inc ebx
    jmp row_loop

end:
    pop ebp
    ret

simul_one_cell:
    push ebp
    mov epb, esp
                                    ; LIFO
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
    jne .end                        ; End
    ; else continue

    pop ebp
    ret

; DEFAUCHY | 2026
