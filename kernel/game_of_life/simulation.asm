; OS-Game-Of-Life
; SIMULATION FILE

[bits 32]                           ; PROTECTED MODE

global simulation                   ; Indicates simulation as a global function

%include "include/constants.inc"    ; Include the contants (define)

; || REGISTERS MAPPING ||
; \/                   \/
;       board => edx
;       i => esi
;       j => edi
;       matrice => [ebp - 8000] (stack)
; ========================
simulation:                         ; Compute and display the next generation of the Game of Life.
    push ebp
    mov ebp, esp

    push esi
    push edi

    mov edx, [ebp + 8]              ; board

    mov esi, 0                      ; i = 0
    mov edi, 0                      ; j = 0

.row_loop_one:
    cmp esi, MAX_ROW_BOARD
    jge .switch_loop_two

.col_loop_one:
    cmp edi, MAX_COL
    jge .row_loop_one_next

    ; matrice[i][j] = simule_one_cell(board, i, j);

.col_loop_one_next:
    inc edi
    jmp .col_loop_one

.row_loop_one_next:
    inc esi
    mov edi, 0
    jmp .row_loop_one

.switch_loop_two:
    mov esi, 0                      ; i = 0
    mov edi, 0                      ; j = 0

.row_loop_two:
    cmp esi, MAX_ROW_BOARD
    jge .end

col_loop_two:
    cmp edi, MAX_COL
    jge .row_loop_two_next

    ; board[i][j] = new_state(matrice[i][j], board[i][j]);

col_loop_two_next:
    inc edi
    jmp .col_loop_two

row_loop_two_next:
    inc esi
    mov edi, 0
    jmp .row_loop_two

end:
    ; print_board(board);
    ; put_cursor(&cursor);
    ; sleep((uint32_t)abs(speed - 100));

    pop edi
    pop esi

    mov esp, ebp
    pop ebp
    ret                             ; void

; DEFAUCHY - RIVIERE | 2026
