; OS-Game-Of-Life
; PORTS FILE

[bits 32]                           ; PROTECTED MODE

global outb                         ; Indicates outb as a global function
global outw                         ; Indicates outw as a global function
global inb                          ; Indicates inb as a global function
global inw                          ; Indicates inw as a global function

; || REGISTERS MAPPING ||
; \/                   \/
;       port => edx
;       data => eax
; ========================
outb:                               ; Write a byte into the specified port
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]              ; port
    mov eax, [ebp + 12]             ; data

    out dx, al

    pop ebp
    ret

; || REGISTERS MAPPING ||
; \/                   \/
;       port => edx
;       data => eax
; ========================
outw:                               ; Write a word into the specified port
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]              ; port
    mov eax, [ebp + 12]             ; data

    out dx, ax

    pop ebp
    ret

; || REGISTERS MAPPING ||
; \/                   \/
;       port => edx
;       data => eax
; ========================
inb:                                ; Read a byte from the specified port
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]              ; port

    xor eax, eax
    in al, dx

    pop ebp
    ret

; || REGISTERS MAPPING ||
; \/                   \/
;       port => edx
;       data => eax
; ========================
inw:                                ; Read a word from the specified port
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]              ; port

    xor eax, eax
    in ax, dx

    pop ebp
    ret

; DEFAUCHY - RIVIERE | 2026
