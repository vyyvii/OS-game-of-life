; OS-Game-Of-Life
; GDT FILE

[bits 16]                           ; PROTECTED MODE
gdt_start:                          ; START SEGMENT

gdt_null:                           ; NULL SEGMENT
    dd 0x0
    dd 0x0

gdt_code:                           ; CODE SEGMENT
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:                           ; DATA SEGMENT
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:                            ; ENG SEGMENT

gdt_descriptor:                     ; Declare the GDT
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start   ; Declare selector for CODE segment
DATA_SEG equ gdt_data - gdt_start   ; Declare selector for DATA segment

; LE CACHEUX, RIVIERE, DEFAUCHY | 2026
