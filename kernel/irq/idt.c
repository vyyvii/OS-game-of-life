// OS-Game-Of-Life
// IDT FILE

#include "irq.h"

struct idt_entry idt[256];
static struct idt_ptr idt_descriptor;

extern void idt_load(struct idt_ptr* idt_ptr);
extern void irq0_handler(void);
extern void irq1_handler(void);

void idt_set_gate(int n, uint32_t handler_adress)
{
    idt[n].offset_low  = handler_adress & 0xffff;
    idt[n].selector    = 0x08;
    idt[n].zero        = 0;
    idt[n].type_attr   = 0x8e;
    idt[n].offset_high = (handler_adress >> 16) & 0xffff;
}

void idt_init(void)
{
    for (int i = 0; i < 256; i++) {
        idt[i].offset_low  = 0;
        idt[i].selector    = 0;
        idt[i].zero        = 0;
        idt[i].type_attr   = 0;
        idt[i].offset_high = 0;
    }
    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base  = (uint32_t)&idt;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_descriptor));
    pic_remap();
    idt_set_gate(0x20, (uint32_t)irq0_handler);
    idt_set_gate(0x21, (uint32_t)irq1_handler);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
