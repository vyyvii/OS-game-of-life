// OS-Game-Of-Life
// KERNEL FILE

#include "kernel.h"

char *video_memory = (char*) 0xb8000;

void kmain(void)
{
    for (int i = 0; i < 80 * 25 * 2; i++)
        video_memory[i] = 0;
    print_string("Kernel C loaded successfully!", 0);
    print_char(' ', 10,2, 0x4f);
    __asm__ volatile ("cli");
    idt_init();
    __asm__ volatile ("sti");
    while(1);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
