// OS-Game-Of-Life
// KEYBOARD FILE

#include "kernel.h"

static int extended = 0;
const char sc_ascii[] = {
    '?', '?', '&', '?', '"', '\'', '(', '-', '?',
    '_', '?', '?', ')', '=', '?', '?',
    'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
    '^', '$', '?', '?',
    'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
    'M', '?', '`', '?',
    '*', 'W', 'X', 'C', 'V', 'B', 'N',
    ',', ';', ':', '!',
    '?', '?', '?', ' '
};

/**
 * @brief Function that handle the UP_ARROW
 * @param cursor The position & the color of the cursor
 */
static void handle_up(cursor_t *cursor)
{
    if (cursor->row < 2)
        cursor->row = 25;
    cursor->row--;
}

/**
 * @brief Function that handle the DOWN_ARROW
 * @param cursor The position & the color of the cursor
 */
static void handle_down(cursor_t *cursor)
{
    if (cursor->row > 23)
        cursor->row = 0;
    cursor->row++;
}

/**
 * @brief Function that handle the LEFT_ARROW
 * @param cursor The position & the color of the cursor
 */
static void handle_left(cursor_t *cursor)
{
    if (cursor->col < 1)
        cursor->col = 80;
    cursor->col--;
}

/**
 * @brief Function that handle the RIGHT_ARROW
 * @param cursor The position & the color of the cursor
 */
static void handle_right(cursor_t *cursor)
{
    if (cursor->col > 78)
        cursor->col = -1;
    cursor->col++;
}

/**
 * @brief Function that handle the keyboard.
 * @note This function is part of the IRQ system. IRQ1 handler call this function.
 */
void keyboard_handler(void)
{
    uint8_t scancode = inb(0x60);
    char letter = sc_ascii[(int)scancode];

    if (scancode > SC_MAX)
        return;
    if (letter == 'Q')
        outw(0x604, 0x2000);
    if (scancode == 0xe0) {
        extended = 1;
        return;
    }
    if (extended) {
        extended = 0;
        print_char(' ', cursor.row, cursor.col, WHITE_ON_BLACK);
        if (scancode == UP_ARROW)
            handle_up(&cursor);
        if (scancode == DOWN_ARROW)
            handle_down(&cursor);
        if (scancode == LEFT_ARROW)
            handle_left(&cursor);
        if (scancode == RIGHT_ARROW)
            handle_right(&cursor);
        print_board(board);
        put_cursor(&cursor);
    }
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
