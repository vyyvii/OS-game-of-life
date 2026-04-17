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
        cursor->row = MAX_ROW - 1;
    else
        cursor->row--;
}

/**
 * @brief Function that handle the DOWN_ARROW
 * @param cursor The position & the color of the cursor
 */
static void handle_down(cursor_t *cursor)
{
    if (cursor->row > MAX_ROW - 2)
        cursor->row = 1;
    else
        cursor->row++;
}

/**
 * @brief Function that handle the LEFT_ARROW
 * @param cursor The position & the color of the cursor
 */
static void handle_left(cursor_t *cursor)
{
    if (cursor->col < 1)
        cursor->col = MAX_COL - 1;
    else
        cursor->col--;
}

/**
 * @brief Function that handle the RIGHT_ARROW
 * @param cursor The position & the color of the cursor
 */
static void handle_right(cursor_t *cursor)
{
    if (cursor->col > MAX_COL - 2)
        cursor->col = 0;
    else
        cursor->col++;
}

static void arrows(uint8_t scancode)
{
    extended = 0;
    if (scancode == UP_ARROW)
        handle_up(&cursor);
    if (scancode == DOWN_ARROW)
        handle_down(&cursor);
    if (scancode == LEFT_ARROW)
        handle_left(&cursor);
    if (scancode == RIGHT_ARROW)
        handle_right(&cursor);
}

static void keys(char letter)
{
    if (letter == 'Q')
        outw(QUIT_QEMU, 0x2000);
    if (letter == 'S')
        board[cursor.row][cursor.col] = !board[cursor.row][cursor.col];
    if (letter == 'R') {
        init_board(&board);
        speed = DEFAULT_SPEED;
    }
    if (letter == ' ')
        go = !go;
    if (letter == 'Z') {
        speed--;
        speed = (speed < MAX_SPEED) ? MAX_SPEED : speed;
    }
    if (letter == 'A') {
        speed++;
        speed = (speed > MIN_SPEED) ? MIN_SPEED : speed;
    }
}

/**
 * @brief Function that handle the keyboard.
 * @note This function is part of the IRQ system. IRQ1 handler call this function.
 */
void keyboard_handler(void)
{
    uint8_t scancode = inb(SCANCODE_REG);
    char letter = sc_ascii[(int)scancode];

    if (letter)
        keys(letter);
    if (scancode == SCANCODE_EXT) {
        extended = 1;
        return;
    }
    if (extended)
        arrows(scancode);
    print_board(board);
    put_cursor(&cursor);
    print_up_line();
}

// DEFAUCHY | 2026
