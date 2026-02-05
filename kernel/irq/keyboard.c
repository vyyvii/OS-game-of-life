// OS-Game-Of-Life
// KEYBOARD FILE

#include "irq.h"

extern void print_string(char *str, int line);

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SC_MAX 57

static char key_buffer[256];

int my_strlen(char s[])
{
    int i = 0;

    while (s[i] != '\0')
        ++i;
    return i;
}

void append(char s[], char n)
{
    int len = my_strlen(s);

    s[len] = n;
    s[len+1] = '\0';
}

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
    append(key_buffer, letter);
    print_string(key_buffer, 5);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
