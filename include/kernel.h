// OS-Game-Of-Life
// KERNEL HEADER

#ifndef KERNEL_H
    #define KERNEL_H
    #include "irq.h"

extern char *video_memory;

void print_char(char c, int col, int row, char attr);
void print_string(char *str, int line);

#endif

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
