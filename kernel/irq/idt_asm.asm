; OS-Game-Of-Life
; GDT FILE

[bits 32]                   ; PROTECTED MODE
global irq0_handler         ; Indicates irq0_handler as a global function
global irq1_handler         ; Indicates irq1_handler as a global function

extern keyboard_handler     ; Make the keyboard_handler function callable in this asm file

%include "include/constants.inc"    ; Include the contants (define)

irq0_handler:               ; Handle the timer interruption
    pusha                   ; Save registers

    mov al, PIC_MASTER      ; EOI PIC master
    out PIC_MASTER, al

    popa                    ; Restore registers
    iret                    ; Return

irq1_handler:               ; Handle the keyboard interruption
    pusha                   ; Save registers

    call keyboard_handler   ; Call the function that will handle the keyboard

    mov al, PIC_MASTER      ; EOI PIC master
    out PIC_MASTER, al

    popa                    ; Restore registers
    iret                    ; Return

; DEFAUCHY | 2026
