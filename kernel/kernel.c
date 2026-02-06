// OS-Game-Of-Life
// KERNEL FILE

#include "kernel.h"

char *video_memory = (char*) 0xb8000;

void kmain(void)
{
    __asm__ volatile ("cli");
    idt_init();
    reset_screen();
    print_string("Kernel C loaded successfully!", 0, 0);
    __asm__ volatile ("sti");
    game();
    while(1);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
