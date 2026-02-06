// OS-Game-Of-Life
// FUNCTIONS FILE

#include "kernel.h"

// Return the size of a string
int my_strlen(char str[])
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return i;
}

// Append a character at the end of a string
void append(char str[], char n)
{
    int len = my_strlen(str);

    str[len] = n;
    str[len + 1] = '\0';
}

// Remove a character at the end of a string
void unappend(char str[])
{
    int len = my_strlen(str);

    str[len - 1] = '\0';
}

// Write a char
void print_char(char c, int row, int col, char attr)
{
    int offset = 2 * (row * 80 + col);

    if (!attr)
        attr = WHITE_ON_BLACK;
    video_memory[offset] = c;
    video_memory[offset + 1] = attr;
}

// Write a string
void print_string(char *str, int row, int col)
{
    int i = 0;

    while (str[i]) {
        print_char(str[i], row, col++, WHITE_ON_BLACK);
        if (col >= 80) {
            col = 0;
            row++;
        }
        i++;
    }
    print_char(' ', row, col++, WHITE_ON_BLACK);
}

// Restore the screen to a black screen
void reset_screen(void)
{
    for (int i = 0; i < 80 * 25 * 2; i++)
        video_memory[i] = 0;
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
