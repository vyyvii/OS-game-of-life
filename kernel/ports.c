// OS-Game-Of-Life
// PORTS FILE

#include "kernel.h"

/**
 * @brief Write a byte into the specified port
 * @param port The port
 * @param date The byte to write
 */
void outb(uint16_t port, uint8_t data)
{
    __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

/**
 * @brief Write a word into the specified port
 * @param port The port
 * @param date The word to write
 */
void outw(uint16_t port, uint16_t data)
{
    __asm__ volatile ("outw %0, %1":: "a"(data), "Nd"(port));
}

/**
 * @brief Read a byte from the specified port
 * @param port The port
 */
uint8_t inb(uint16_t port)
{
    uint8_t ret;

    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/**
 * @brief Read a word from the specified port
 * @param port The port
 */
uint16_t inw(uint16_t port)
{
    uint16_t ret;

    __asm__ volatile ("inw %1, %0": "=a"(ret): "Nd"(port));
    return ret;
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
