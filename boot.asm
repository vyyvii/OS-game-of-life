[org 0x7c00]

mov bx, message
call print_function

jmp $ ; LOOP FOREVER

%include "print_function.asm"

message:
    db 'Hello World', 0

times 510-($-$$) db 0
dw 0xaa55