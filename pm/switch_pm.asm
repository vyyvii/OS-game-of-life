; SWITCH TO PM FILE

[bits 16]                   ; REAL MODE
switch_to_pm:
    cli                     ; Stop CPU interrupt
    lgdt [gdt_descriptor]   ; Give to the CPU the GDT

    mov eax, cr0            ; Trigger the CPU register CR0
    or eax, 1               ; in order to activate the
    mov cr0, eax            ; protected mode

    jmp CODE_SEG:init_pm    ; Long jump to the protected mode to avoid pipelining

[bits 32]                   ; PROTECTED MODE
init_pm:
    mov ax, DATA_SEG        ; Copies registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM           ; Start the protected mode

; LE CACHEUX, RIVIERE, DEFAUCHY | 2026
