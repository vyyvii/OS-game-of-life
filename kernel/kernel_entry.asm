; KERNEL ENTRY FILE

global _start

[bits 32]
[extern kmain]

_start:
  call kmain
  jmp $

; LE CACHEUX, RIVIERE, DEFAUCHY | 2026
