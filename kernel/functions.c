// OS-Game-Of-Life
// FUNCTIONS FILE

#include "kernel.h"

/**
 * @brief Return the size of a string
 * @param str The string
 */
int my_strlen(char str[])
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return i;
}

/**
 * @brief Append a character at the end of a string
 * @param str The string
 * @param n The character to append
 */
void append(char str[], char n)
{
    int len = my_strlen(str);

    str[len] = n;
    str[len + 1] = '\0';
}

/**
 * @brief Remove a character at the end of a string
 * @param str The string
 */
void unappend(char str[])
{
    int len = my_strlen(str);

    str[len - 1] = '\0';
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
