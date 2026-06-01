; OS-Game-Of-Life
; BOOT FILE

; ===============================
; BOOT SECTOR
; ===============================
[bits 16]                       ; REAL MODE
[org 0x7c00]

%include "include/constants.inc"; Include the contants (define)

start:
    cli                         ; Disable CPU interruptions

    xor ax, ax                  ; Init segments
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov [BOOT_DRIVE], dl        ; save boot drive

    mov bp, 0x9000              ; Stack
    mov sp, bp

    mov bx, MSG_REAL_MODE       ; Load the string into bx
    call print_rm               ; Print bx

    call load_kernel            ; Load the kernel

    call switch_to_pm           ; Go from real to protected mode

    jmp $                       ; HANG

; ===============================
; INCLUDES
; ===============================
%include "print_rm.asm"
%include "pm/gdt.asm"
%include "pm/print_pm.asm"
%include "pm/switch_pm.asm"
%include "periph/disk_load.asm"

; ===============================
; PROTECTED MODE
; ===============================
[bits 32]

BEGIN_PM:
    push ebx                    ; ebx (& esi/edi) are callee-saved...

    mov ebx, MSG_PROT_MODE      ; Load string into ebx
    mov ecx, 22                 ; Load the size of the string into ecx
    call print_pm               ; Print ebx

    pop ebx                     ; ... so we have to push them on the stack & finally, pop them

    call KERNEL_OFFSET          ; Go to the kernel

    jmp $                       ; HANG

; ===============================
; GLOBAL VARIABLES
; ===============================
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "32-bit Protected Mode", 0

; ===============================
; PADDING & SIGNATURE
; ===============================
times 510-($-$$) db 0           ; PADDING
dw 0xaa55 ;(BIG ENDIAN)         ; BOOTLOADER SIGNATURE

; WORKSHOP | 2026
