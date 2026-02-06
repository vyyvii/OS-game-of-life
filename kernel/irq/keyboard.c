// OS-Game-Of-Life
// KEYBOARD FILE

#include "kernel.h"

static char key_buffer[256];
static int col = 5;

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

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;

    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void keyboard_handler(void)
{
    uint8_t scancode = inb(0x60);
    char letter = sc_ascii[(int)scancode];

    if (scancode > SC_MAX)
        return;
    if (scancode == BACKSPACE)
        unappend(key_buffer);
    else if (scancode == ENTER) {
        col++;
        key_buffer[0] = '\0';
    }
    else
        append(key_buffer, letter);
    print_string(key_buffer, col, 0);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
