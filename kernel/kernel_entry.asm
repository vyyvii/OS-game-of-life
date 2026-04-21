; OS-Game-Of-Life
; KERNEL ENTRY FILE

[bits 32]                           ; PROTECTED MODE

global _start                       ; Indicates _start as a global function
[extern kmain]                      ; Indicates kmain as an extern function

_start:                             ; Function call in boot.asm to start the kernel
  cli

  mov esp, stack_top
  and esp, 0xFFFFFFF0

  call kmain                        ; Call the kernel

.hang:
  jmp .hang                         ; HANG

section .bss
stack_bottom:
    resb 8192
stack_top:

; DEFAUCHY | 2026
