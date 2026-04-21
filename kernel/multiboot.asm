; OS-Game-Of-Life
; SCREEN FILE

[bits 32]                       ; PROTECTED MODE

%include "include/constants.inc"; Include the contants (define)

section .multiboot
align 4

dd 0x1BADB002                   ; magic
dd 0x0                          ; flags
dd -(0x1BADB002)                ; checksum

; DEFAUCHY | 2026
