; OS-Game-Of-Life
; PORTS FILE

[bits 32]                           ; PROTECTED MODE

global outb                         ; Indicates outb as a global function
global outw                         ; Indicates outw as a global function
global inb                          ; Indicates inb as a global function
global inw                          ; Indicates inw as a global function

outb:                               ; Write a byte into the specified port
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]              ; port
    mov eax, [ebp + 12]             ; data

    out dx, al

    pop ebp
    ret

outw:                               ; Write a word into the specified port
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]              ; port
    mov eax, [ebp + 12]             ; data

    out dx, ax

    pop ebp
    ret

inb:                                ; Read a byte from the specified port
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]              ; port

    in al, dx

    pop ebp
    ret

inw:                                ; Read a word from the specified port
    push ebp
    mov ebp, esp

    mov edx, [ebp + 8]              ; port

    in ax, dx

    pop ebp
    ret

; DEFAUCHY | 2026
