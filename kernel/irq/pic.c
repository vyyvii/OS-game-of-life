// OS-Game-Of-Life
// PIC FILE

#include "kernel.h"

/**
 * @brief Remap the PIC because default value of the PIC are mapped with CPU registers value.
 * @note The new adress are by convention 0x20 & 0x21
 */
void pic_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
