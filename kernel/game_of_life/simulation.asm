; OS-Game-Of-Life
; SIMULATION FILE

[bits 32]                           ; PROTECTED MODE

global simulation                   ; Indicates simulation as a global function
[extern] simule_one_cell            ; Indicates simule_one_cell as an external function
[extern] new_state                  ; Indicates new_state as an external function
[extern] print_board                ; Indicates print_board as an external function
[extern] put_cursor                 ; Indicates put_cursor as an external function
[extern] sleep                      ; Indicates sleep as an external function

[extern] cursor                     ; Indicates cursor as an external variable
[extern] speed                      ; Indicates speed as an external variable

%include "include/constants.inc"    ; Include the contants (define)

; || REGISTERS MAPPING ||
; \/                   \/
;       board => edx
;       i => esi
;       j => edi
;       matrice => [ebp - 8000] (stack)
;       matrice adress => ebx
;       tmp => ecx
;       output => eax (& for matrice in col_loop_two)
; ========================
simulation:                         ; Compute and display the next generation of the Game of Life.
    push ebp
    mov ebp, esp

    push ebx
    push esi
    push edi

    sub esp, 8000                   ; matrice | 25(row) * 80(col) * 4(int size) = 8000
    lea ebx, [ebp - 8012]           ; matrice adress

    mov edx, [ebp + 8]              ; board

    mov esi, 0                      ; i = 0
    mov edi, 0                      ; j = 0

; =========
; PHASE ONE
; =========
.row_loop_one:                      ; ANALYZE BOARD
    cmp esi, MAX_ROW_BOARD
    jge .switch_loop_two            ; continue if i < MAX_ROW_BOARD

.col_loop_one:
    cmp edi, MAX_COL
    jge .row_loop_one_next          ; continue if j < MAX_COL

    ; matrice[i][j] = simule_one_cell(board, i, j);
    push edx                        ; Save register (board)
    push esi                        ; Save register (i)
    push edi                        ; Save register (j)
    push ebx                        ; Save matrice address

    push edi                        ; Pass parameters (j)
    push esi                        ; Pass parameters (i)
    push edx                        ; Pass parameters (board)
    call simule_one_cell            ; Function call (int, return in eax)
    add esp, 12                     ; Clean stack

    pop ebx                         ; Restore matrice address
    pop edi                         ; Get saved register (j)
    pop esi                         ; Get saved register (i)
    pop edx                         ; Get saved register (board)

    ; addr = base + (i * MAX_COL + j) * 4 (MATRICE)
    mov ecx, esi                    ; addr = i
    imul ecx, MAX_COL               ; addr *= MAX_COL
    add ecx, edi                    ; addr += j
    shl ecx, 2                      ; addr *= 4 (bit shift left)
    add ecx, ebx                    ; addr += base
    mov [ecx], eax                  ; Put simule_one_cell result in matrice[i][j]

.col_loop_one_next:
    inc edi                         ; j++
    jmp .col_loop_one

.row_loop_one_next:
    inc esi                         ; i++
    mov edi, 0                      ; j = 0
    jmp .row_loop_one

; =========
; PHASE TWO
; =========
.switch_loop_two:                   ; MODIFY BOARD
    mov esi, 0                      ; i = 0
    mov edi, 0                      ; j = 0

.row_loop_two:
    cmp esi, MAX_ROW_BOARD
    jge .finish                     ; continue if i < MAX_ROW_BOARD

.col_loop_two:
    cmp edi, MAX_COL
    jge .row_loop_two_next          ; continue if j < MAX_COL

    ; board[i][j] = new_state(matrice[i][j], board[i][j]);
    ; addr = base + (i * MAX_COL + j) * 4 (BOARD)
    mov ecx, esi                    ; addr = i
    imul ecx, MAX_COL               ; addr *= MAX_COL
    add ecx, edi                    ; addr += j
    shl ecx, 2                      ; addr *= 4 (bit shift left)
    add ecx, edx                    ; addr += base
    push ecx                        ; Save register (board[i][j])
    mov ecx, [ecx]                  ; board[i][j]

    ; addr = base + (i * MAX_COL + j) * 4 (MATRICE)
    mov eax, esi                    ; addr = i
    imul eax, MAX_COL               ; addr *= MAX_COL
    add eax, edi                    ; addr += j
    shl eax, 2                      ; addr *= 4 (bit shift left)
    add eax, ebx                    ; addr += base
    mov eax, [eax]                  ; matrice[i][j]

    push ecx                        ; Pass parameters (board[i][j])
    push eax                        ; Pass parameters (matrice[i][j])
    call new_state                  ; Function call (int, return in eax)
    add esp, 8                      ; Clean stack

    pop ecx                         ; Get saved register (board[i][j])

    mov [ecx], eax                  ; Put new_state result in board[i][j]

.col_loop_two_next:
    inc edi                         ; j++
    jmp .col_loop_two

.row_loop_two_next:
    inc esi                         ; i++
    mov edi, 0                      ; j = 0
    jmp .row_loop_two

; ======
; ENDING
; ======
.finish:                            ; Print the board & the cursor. Then, sleep
    ; print_board(board);
    push edx                        ; Pass the parameters (board)
    call print_board                ; void
    add esp, 4                      ; clean stack

    ; put_cursor(&cursor);
    lea ecx, [cursor]               ; Get the cursor adress (extern)
    push ecx                        ; Pass the parameters (cursor)
    call put_cursor                 ; void
    add esp, 4                      ; clean stack

    ; sleep((uint32_t)abs(speed - 100));
    mov ecx, [speed]                ; tmp = speed
    sub ecx, 100                    ; tmp -= 100
    cmp ecx, 0
    jge .positive                   ; if tmp < 0, then:
    neg ecx                         ; tmp = -tmp

.positive:                          ; else if tmp >= 0, do nothing
    push ecx                        ; Pass the parameters (tmp)
    call sleep                      ; void
    add esp, 4                      ; clean stack

end:
    add esp, 8000                   ; clean stack

    pop edi
    pop esi
    pop ebx

    pop ebp
    ret                             ; void

; DEFAUCHY - RIVIERE | 2026
