; OS-Game-Of-Life
; BOOT FILE

; ===============================
; BOOT SECTOR
; ===============================
[bits 16]
[org 0x7c00]

KERNEL_OFFSET equ 0x1000

start:
    cli

    xor ax, ax                  ; Init segments
    mov ds, ax
    mov es, ax
    mov ss, ax

    mov [BOOT_DRIVE], dl        ; save boot drive

    mov bp, 0x9000              ; Stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_rm

    call load_kernel            ;  ADD: loading kernel

    call switch_to_pm

    jmp $

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
    mov ebx, MSG_PROT_MODE
    mov ecx, 22
    call print_pm

    call KERNEL_OFFSET

    jmp $

; ===============================
; GLOBAL VARIABLES
; ===============================
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0x0d, 0x0a, 0
MSG_PROT_MODE db "32-bit Protected Mode", 0

; ===============================
; PADDING & SIGNATURE
; ===============================
times 510-($-$$) db 0
dw 0xaa55

; DEFAUCHY | 2026
