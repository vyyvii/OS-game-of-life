// OS-Game-Of-Life
// IRQ HEADER

#ifndef IRQ_H
    #define IRQ_H
    #define BACKSPACE 0x0E
    #define ENTER 0x1C
    #define SC_MAX 57
    #include "types.h"

// IDT (interrupt descriptor table)
struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attr;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init(void);

// PIC (programmable interrupt transistor)
void pic_remap(void);

#endif

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
