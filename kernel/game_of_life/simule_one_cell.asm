; OS-Game-Of-Life
; SIMULE_ONE_CELL FILE

[bits 32]                           ; PROTECTED MODE

global simule_one_cell              ; Indicates simule_one_cell as a global function

%include "include/constants.inc"    ; Include the contants (define)

; || REGISTERS MAPPING ||
; \/                   \/
;       board => edx
;       i => esi
;       j => [ebp - 4] (stack)
;       ii => ebx
;       jj => edi
;       cpt => ecx
;       tmp => eax
; ========================
simule_one_cell:                    ; Count the number of alive neighbors around a specific cell.
    push ebp
    mov ebp, esp

    push ebx
    push esi
    push edi

    sub esp, 4                      ; SAVE SPACE ON STACK

    mov edx, [ebp + 8]              ; board
    mov esi, [ebp + 12]             ; i | Row index of the target cell
    mov eax, [ebp + 16]             ; j | Column index of the target cell
    mov [ebp - 4], eax              ; save j locally

    mov ecx, 0                      ; cpt = 0
    mov ebx, esi                    ; ii = i
    sub ebx, 1                      ; ii--

ii_loop:
    mov eax, esi                    ; END CONDITION (continue if ii <= i + 1)
    inc eax
    cmp ebx, eax
    jg end                          ; if ii > i + 1

    cmp ebx, 0
    jl ii_next                      ; if ii < 0
    ; OR
    cmp ebx, MAX_ROW_BOARD
    jge ii_next                     ; if ii >= MAX_ROW_BOARD

    mov edi, [ebp - 4]              ; jj = j
    sub edi, 1                      ; jj--

jj_loop:
    mov eax, [ebp - 4]              ; END_LOOP CONDITION (continue if jj <= j + 1)
    inc eax
    cmp edi, eax
    jg ii_next                      ; if jj > j + 1

    cmp edi, 0
    jl jj_next                      ; if jj < 0
    ; OR
    cmp edi, MAX_COL
    jge jj_next                     ; if jj >= MAX_COL
    ; OR
    cmp ebx, esi
    je .if_equal                    ; ( if ii == i

    jmp check_cell                  ; // ELSE //

.if_equal:                          ; AND
    cmp edi, [ebp - 4]
    je jj_next                      ; if jj == j )

check_cell:
    ; addr = base + (ii * MAX_COL + jj) * 4
    mov eax, ebx                    ; addr = ii
    imul eax, MAX_COL               ; addr *= MAX_COL
    add eax, edi                    ; addr += jj
    shl eax, 2                      ; addr *= 4 (bit shift left)
    add eax, edx                    ; addr += base
    ; Now we have &board[ii][jj]
    mov eax, [eax]                  ; Put the value of board[ii][jj] in eax

    cmp eax, 1
    je .put_one                     ; if board[ii][jj] == 1

    jmp jj_next                     ; // ELSE // (do nothing)

.put_one:
    inc ecx                         ; cpt++

jj_next:
    inc edi                         ; jj++
    jmp jj_loop

ii_next:
    inc ebx                         ; ii++
    jmp ii_loop

end:
    mov eax, ecx                    ; CONVENTION: return value in eax

    add esp, 4                      ; free local variable

    pop edi
    pop esi
    pop ebx

    mov esp, ebp
    pop ebp
    ret                             ; INT | Number of alive neighboring cells

; DEFAUCHY - RIVIERE | 2026
