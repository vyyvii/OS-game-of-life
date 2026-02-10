// OS-Game-Of-Life
// IDT FILE

#include "kernel.h"

struct idt_entry idt[256];              // The IDT
static struct idt_ptr idt_descriptor;   // The descripror of the IDT

extern void irq0_handler(void);         // Call the ASM function that handle IRQ0
extern void irq1_handler(void);         // Call the ASM function that handle IRQ1

/**
 * @brief Function use to set the gate for an IRQ.
 * @param n The HEXA code of the IRQ
 * @param handler_adress The hadress of the handler
 */
void idt_set_gate(int n, uint32_t handler_adress)
{
    idt[n].offset_low  = handler_adress & 0xffff;
    idt[n].selector    = 0x08;
    idt[n].zero        = 0;
    idt[n].type_attr   = 0x8e;
    idt[n].offset_high = (handler_adress >> 16) & 0xffff;
}

/**
 * @brief Initialise the IDT (Interrupt Descriptor Table) & the gates (IRQ0/1).
 * @note IRQ0 is the timer interruption.
 * @note IRQ1 is the keyboard interruption.
 */
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
    pic_remap();        // REMAP the PIC (Programmable Interrupt Transistor)
    idt_set_gate(0x20, (uint32_t)irq0_handler);
    idt_set_gate(0x21, (uint32_t)irq1_handler);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
