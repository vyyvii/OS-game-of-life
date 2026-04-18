// OS-Game-Of-Life
// AUX FILE

#include "kernel.h"

/**
 * @brief Function that return the absolute value of an integer
 * @param nb (int) The number to test
 */
int abs(int nb)
{
    return nb >= 0 ? nb : -nb;
}

/**
 * @brief Function that print an integer
 * @param n (int) The number to print
 * @param row (int) The row where we want to print the number
 * @param col (int) The column where we want to print the number
 * @param attr (int) The attribut of the string
 */
void print_int(int n, int row, int col, int attr)
{
    char buffer[MAX_INT_SIZE];
    int i = 0;

    if (n == 0) {
        buffer[i] = '0';
        i++;
    } else {
        while (n > 0) {
            buffer[i] = (n % 10) + '0';
            i++;
            n /= 10;
        }
    }
    for (int j = 0; j < MAX_INT_SIZE; j++)
        print_char(' ', row, col + j, attr);
    for (int j = 0; j < i; j++)
        print_char(buffer[i - j - 1], row, col + j, attr);
}

/**
 * @brief Function that print the upper line.
 * @note This line isn't part of the board.
 */
void print_up_line(void)
{
    for (int i = 0; i < MAX_COL; i++)
        print_char(' ', 0, i, WHITE_ON_GRAY);
    print_string("LifeOS", 0, 1, WHITE_ON_GRAY);
    print_string("Victor Defauchy", 0, 12, WHITE_ON_GRAY);
    print_string("Speed:", 0, 32, WHITE_ON_GRAY);
    print_int(speed, 0, 39, WHITE_ON_GRAY);
    if (speed == MAX_SPEED)
        print_char('%', 0, 42, WHITE_ON_GRAY);
    else if (speed < 10)
        print_char('%', 0, 40, WHITE_ON_GRAY);
    else
        print_char('%', 0, 41, WHITE_ON_GRAY);
    print_string("Simulation:", 0, 48, WHITE_ON_GRAY);
    print_string((go) ? "ON" : "OFF", 0, 60, WHITE_ON_GRAY);
    print_string("Q to quit", 0, 68, WHITE_ON_GRAY);
    // | LifeOS     Victor Defauchy     Speed: 100%     Simulation: OFF     Q to quit     |
    // |00    0     1             2     3    3 3  4     4           6       6            8|
    // |01    6     2             6     2    7 9  2     8           0       8            0|
}

// DEFAUCHY | 2026
