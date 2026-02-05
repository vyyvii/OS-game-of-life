; DISK LOAD FILE

[bits 16]                                   ; REAL MODE

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

MSG_ERROR db "DISK ERROR!", 0

; LE CACHEUX, RIVIERE, DEFAUCHY | 2026
