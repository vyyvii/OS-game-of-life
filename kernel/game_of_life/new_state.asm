; OS-Game-Of-Life
; NEW_STATE FILE

[bits 32]                           ; PROTECTED MODE

global new_state                    ; Indicates new_state as a global function

%include "include/constants.inc"    ; Include the contants (define)

; || REGISTERS MAPPING ||
; \/                   \/
;       neighbors => ebx
;       state => ecx
;       output => eax
; ========================
new_state:                          ; Compute the next state of a cell based on its neighbors.
    push ebp
    mov ebp, esp

    push ebx

    mov ebx, [ebp + 8]              ; neighbors | Number of alive neighboring cells
    mov ecx, [ebp + 12]             ; state | Current state of the cell (0 = dead, 1 = alive)
    mov eax, 0                      ; output init to 0

; Applies Conway's Game of Life rules:
; - A dead cell becomes alive if it has exactly 3 neighbors.
; - A living cell survives if it has 2 or 3 neighbors.
; - Otherwise, the cell dies or remains dead.

    cmp ecx, 0
    jne .alive                      ; if state != 0 (cell is alive)
    ; else (cell is dead)
    cmp ebx, 3
    je .alive_next                  ; if neighboors == 3

    jmp .dead                       ; OTHERWISE cell stay dead

.alive:                             ; AND
    cmp ebx, 2
    jl .dead                        ; if neighboors < 2, cell die
    ; OR
    cmp ebx, 3
    jg .dead                        ; if neighboors > 3, cell die

.alive_next:
    mov eax, 1                      ; cell alive
    jmp end

.dead:
    mov eax, 0                      ; DEAD mean cell = 0

end:
    pop ebx

    mov esp, ebp
    pop ebp
    ; CONVENTION: return value in eax (already in)
    ret                             ; INT | The new state of the cell (0 = dead, 1 = alive)

; DEFAUCHY - RIVIERE | 2026
