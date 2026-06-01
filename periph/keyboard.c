// OS-Game-Of-Life
// KEYBOARD FILE

#include "kernel.h"

static int extended = 0;
static const char sc_ascii[] = {
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

/**
 * @brief Function that handle all of the arrows
 * @param scancode The code of one of the arrows
 */
static void arrows(uint8_t scancode)
{
    if (scancode == UP_ARROW)
        handle_up(&cursor);
    if (scancode == DOWN_ARROW)
        handle_down(&cursor);
    if (scancode == LEFT_ARROW)
        handle_left(&cursor);
    if (scancode == RIGHT_ARROW)
        handle_right(&cursor);
    refresh_screen(board);
}

/**
 * @brief Reset the screen and halt the CPU.
 * @note While stop a computer is a hard task, halt it & print a message is way easier.
 */
static void quit_screen_real(void)
{
    reset_screen();
    print_string("LifeOS stopped. You may now power off the computer.", 12, 15, WHITE_ON_BLACK);
    __asm__ volatile("cli");                   // Disable CPU interruptions
    while (1)                                  // HANG
        __asm__ volatile("hlt");               // Halt the CPU
}

/**
 * @brief Function that handle the KEYS 'q', 's', 'r', ' ', 'z' & 'a'
 * @param letter The letter
 */
static void keys(char letter)
{
    if (letter == 'Q') {
        outw(QUIT_QEMU, 0x2000);                // Stop the OS on qemu (only works on qemu)
        quit_screen_real();                     // Else, go to quit_screen_real
    }
    if (letter == 'S')
        board[cursor.row - 1][cursor.col] = !board[cursor.row - 1][cursor.col];
    if (letter == 'R') {
        init_board(board);
        speed = DEFAULT_SPEED;
    }
    if (letter == ' ' && speed)
        go = !go;
    if (letter == 'Z') {
        speed++;
        speed = (speed > MAX_SPEED) ? MAX_SPEED : speed;
        go = (speed != MIN_SPEED) ? 1 : go;
    }
    if (letter == 'A') {
        speed--;
        speed = (speed < MIN_SPEED) ? MIN_SPEED : speed;
        go = (speed == MIN_SPEED) ? 0 : go;
    }
    if (letter == 'G')
        randomize_board(board, 25);
}

/**
 * @brief Function that handle the keyboard. SET1 only (PS/2)
 */
void scancode_handler(voir)
{
    uint8_t scancode = inb(SCANCODE_REG);           // Read the scancode

    if (scancode == SCANCODE_EXT) {                 // If it is an extended scancode (arrows)...
        extended = 1;                               // ...put global variables extended to one
        return;                                     // Return to be ready to catch the real value
    }
    if (extended) {
        if (scancode == SCANCODE_FAKE_PRESS || scancode == SCANCODE_FAKE_RELEASE)
            return;                                 // On some computer, we can deal with fake scancode arround the real one
        extended = 0;
        if (scancode & RELASE_MASK)                 // If scancode & 0x80 == 0, it mean that the key is just realease, so skip
            return;
        arrows(scancode);                           // Handle the correct arrow
    }
    if (scancode & RELASE_MASK || scancode >= sizeof(sc_ascii))
        return;                                     // Check for the release & the out of range value
    keys(sc_ascii[scancode]);                       // Handle the correct key
    refresh_screen(board);
}

/**
 * @brief Function that handle the keyboard. Empty the IRQ1 buffer by calling
 * the function while the status byte (0x64) is still to one.
 * @note This function is part of the IRQ system. IRQ1 handler call this function.
 */
void keyboard_handler(void)
{
    while (inb(SCANCODE_STATUS) & 1)
        scancode_handler();
}

// DEFAUCHY - RIVIERE | 2026
