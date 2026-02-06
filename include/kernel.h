// OS-Game-Of-Life
// KERNEL HEADER

#ifndef KERNEL_H
    #define KERNEL_H
    #define WHITE_ON_BLACK 0x0f
    #define BLACK_ON_WHITE 0xf0
    #include "irq.h"
    #include "game.h"

extern char *video_memory;

int my_strlen(char str[]);
void append(char str[], char n);
void unappend(char str[]);
void print_char(char c, int row, int col, char attr);
void print_string(char *str, int row, int col);
void reset_screen(void);

#endif

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
