; OS-Game-Of-Life
; PIC FILE

[bits 32]                           ; PROTECTED MODE

global pic_remap                    ; Indicates pic_remap as a global function

pic_remap:                          ; Remap the PIC because default value of the PIC are mapped with CPU registers value.
    push ebp
    mov ebp, esp

    ; NOTE : The new adress are by convention 0x20 & 0x21
    ; ICW1
    mov al, 0x11
    mov dx, 0x20
    out dx, al

    mov dx, 0xA0
    out dx, al

    ; ICW2 (offsets)
    mov al, 0x20
    mov dx, 0x21
    out dx, al

    mov al, 0x28
    mov dx, 0xA1
    out dx, al

    ; ICW3
    mov al, 0x04
    mov dx, 0x21
    out dx, al

    mov al, 0x02
    mov dx, 0xA1
    out dx, al

    ; ICW4
    mov al, 0x01
    mov dx, 0x21
    out dx, al

    mov dx, 0xA1
    out dx, al

    ; masks (enable all)
    mov al, 0x00
    mov dx, 0x21
    out dx, al

    mov dx, 0xA1
    out dx, al

    pop ebp
    ret

; DEFAUCHY | 2026
