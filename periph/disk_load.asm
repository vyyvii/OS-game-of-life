; OS-Game-Of-Life
; DISK LOAD FILE

[bits 16]                       ; REAL MODE

load_kernel:                    ; Function that load the kernel in memory
    pusha

    mov bx, KERNEL_OFFSET       ; 0x1000
    mov dh, 7                   ; sectors = (kernel_size + 511) / 512 = 3699 / 512 =~ 7
    mov dl, [BOOT_DRIVE]

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00

    int 0x13                    ; Call BIOS disk service
    jc disk_error               ; Jump if carry (if carry flag is set, error occurred)

    popa
    ret

disk_error:                     ; Function printing an error message
    mov bx, MSG_ERROR
    call print_rm

    cli                         ; Disable CPU interruptions
    hlt                         ; HOLD

MSG_ERROR db "DISK ERROR!", 0   ; ERROR MESSAGE

; DEFAUCHY - RIVIERE | 2026
