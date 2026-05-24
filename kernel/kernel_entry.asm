; OS-Game-Of-Life
; KERNEL ENTRY FILE

[bits 32]                           ; PROTECTED MODE

global _start                       ; Indicates _start as a global function
[extern kmain]                      ; Indicates kmain as an extern function

; || REGISTERS MAPPING ||
; \/                   \/
; ========================

_start:                             ; Function call in boot.asm to start the kernel
  call kmain                        ; Call the kernel
  jmp $                             ; HANG

; DEFAUCHY - RIVIERE | 2026
