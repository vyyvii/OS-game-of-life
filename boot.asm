; BOOT FILE

[bits 16]
[org 0x7c00]

    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_rm

    call switch_to_pm

    jmp $

%include "print_rm.asm"
%include "gdt.asm"
%include "print_pm.asm"
%include "switch_pm.asm"

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    mov ecx, 12
    call print_pm

    mov ebx, MSG_HELLO_WORLD
    mov ecx, 14
    call print_pm

    jmp $

MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Now in 32-bit Protected Mode", 0
MSG_HELLO_WORLD db "Hello World !", 0

times 510-($-$$)  db 0
dw 0xaa55
