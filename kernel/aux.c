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
    print_string("Riviere - Defauchy", 0, 12, WHITE_ON_GRAY);
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

/**
 * @brief Wrap a set of usefull functions calls.
 * @param board The board of the game.
 * @note This refresh the all board.
 */
void refresh_screen(int board[MAX_ROW_BOARD][MAX_COL])
{
    print_board(board);
    put_cursor(&cursor);
    print_up_line();
}

/**
 * @brief The left oscillator.
 * @param board The board of the game.
 */
static void left(int board[MAX_ROW_BOARD][MAX_COL])
{
    for (int i = 0; i < 6; i++){
        board[6][9 + i] = 1;
        board[7][9 + i] = 1;
    }
    for (int i = 0; i < 6; i++){
        board[9 + i][9] = 1;
        board[9 + i][10] = 1;
    }
    for (int i = 0; i < 6; i++) {
        board[6 + i][16] = 1;
        board[6 + i][17] = 1;
    }
    for (int i = 0; i < 6; i++) {
        board[13][12 + i] = 1;
        board[14][12 + i] = 1;
    }
}

/**
 * @brief The right oscillator.
 * @param board The board of the game.
 */
static void right(int board[MAX_ROW_BOARD][MAX_COL])
{
    // UP
        // LEFT
    for (int i = 0; i < 3; i++)
        board[6][45 + i] = 1;
    for (int i = 0; i < 3; i++)
        board[8 + i][43] = 1;
    for (int i = 0; i < 3; i++)
        board[11][45 + i] = 1;
    for (int i = 0; i < 3; i++)
        board[8 + i][48] = 1;
        // RIGHT
    for (int i = 0; i < 3; i++)
        board[6][51 + i] = 1;
    for (int i = 0; i < 3; i++)
        board[8 + i][55] = 1;
    for (int i = 0; i < 3; i++)
        board[11][51 + i] = 1;
    for (int i = 0; i < 3; i++)
        board[8 + i][50] = 1;

    // DOWN
        // LEFT
    for (int i = 0; i < 3; i++)
        board[13][45 + i] = 1;
    for (int i = 0; i < 3; i++)
        board[14 + i][43] = 1;
    for (int i = 0; i < 3; i++)
        board[18][45 + i] = 1;
    for (int i = 0; i < 3; i++)
        board[14 + i][48] = 1;

        // RIGHT
    for (int i = 0; i < 3; i++)
        board[13][51 + i] = 1;
    for (int i = 0; i < 3; i++)
        board[14 + i][55] = 1;
    for (int i = 0; i < 3; i++)
        board[18][51 + i] = 1;
    for (int i = 0; i < 3; i++)
        board[14+ i][50] = 1;
}

/**
 * @brief demo_mode is a function to show for any user what's game of life and
 * lifeos !
 * @param board The board of the game.
 */
void demo_mode(int board[MAX_ROW_BOARD][MAX_COL])
{
    init_board(board);
    left(board);
    right(board);
}

// DEFAUCHY - RIVIERE | 2026
