// KERNEL FILE

#include "print_string.c"

void kmain(void)
{
    for (int i = 0; i < 80 * 25 * 2; i++)
        video_memory[i] = 0;
    print_string("Kernel C loaded successfully!");
    print_char(' ', 10,2, 0x4f);
    while(1);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
