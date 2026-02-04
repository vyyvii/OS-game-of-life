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

    sti

    mov bx, MSG_REAL_MODE
    call print_rm

    call load_kernel            ;  ADD: loading kernel

    call switch_to_pm

    jmp $

; ===============================
; LOAD KERNEL
; ===============================
load_kernel:
    pusha

    mov bx, KERNEL_OFFSET       ; 0x1000
    mov dh, 15                  ; 15 sectors
    mov dl, [BOOT_DRIVE]

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00

    int 0x13

    jc disk_error

    popa
    ret

disk_error:
    mov bx, MSG_ERROR
    call print_rm
    cli
    hlt

; ===============================
; DATA
; ===============================
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0x0d, 0x0a, 0
MSG_PROT_MODE db "32-bit Protected Mode", 0
MSG_HELLO_WORLD db "Hello World!", 0
MSG_ERROR db "DISK ERROR!", 0

; ===============================
; INCLUDES
; ===============================
%include "print_rm.asm"
%include "gdt.asm"
%include "print_pm.asm"
%include "switch_pm.asm"


; ===============================
; PROTECTED MODE
; ===============================
[bits 32]
BEGIN_PM:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    mov ebx, MSG_PROT_MODE
    mov ecx, 22
    call print_pm

    call KERNEL_OFFSET

    jmp $

times 510-($-$$) db 0
dw 0xaa55