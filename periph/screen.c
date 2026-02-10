// OS-Game-Of-Life
// SCREEN FILE

#include "kernel.h"

/**
 * @brief Write a character on the screen
 * @param c The character to print
 * @param row The row
 * @param col The col
 * @param attr The attributes (color & background)
 */
void print_char(char c, int row, int col, char attr)
{
    int offset = 2 * (row * MAX_COL + col);

    if (!attr)
        attr = WHITE_ON_BLACK;
    video_memory[offset] = c;
    video_memory[offset + 1] = attr;
}

/**
 * @brief Write a string on the screen
 * @param str The string to print
 * @param row The row
 * @param col The col
 * @param color The attributes (color & background)
 * @note Call print_char()
 */
void print_string(char *str, int row, int col, int color)
{
    for (int i = 0; str[i]; i++) {
        print_char(str[i], row, col++, color);
        if (col >= MAX_COL) {
            col = 0;
            row++;
        }
    }
    print_char(' ', row, col++, color);
}

/**
 * @brief Reset the screen. Black screen.
 */
void reset_screen(void)
{
    for (int i = 0; i < MAX_COL * MAX_ROW * 2; i++)
        video_memory[i] = 0;
}

/**
 * @brief Print the cursor
 * @param cursor The cursor (row, col & color)
 */
void put_cursor(cursor_t *cursor)
{
    print_char(' ', cursor->row, cursor->col, cursor->color);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
