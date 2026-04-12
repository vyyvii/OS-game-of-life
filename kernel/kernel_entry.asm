; OS-Game-Of-Life
; KERNEL ENTRY FILE

global _start

[bits 32]
[extern kmain]

_start:
  call kmain
  jmp $

; DEFAUCHY | 2026
