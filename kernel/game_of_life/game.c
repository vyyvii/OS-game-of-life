// OS-Game-Of-Life
// FUNCTIONS FILE

#include "kernel.h"

/**
 * @brief Function that initialise the board with all the cells in the state 0
 * @param board The board with a size of 24 by 80
 * @note VGA text mode is 25 by 80 cells large, but here, the first line is infos.
 */
void init_board(int board[MAX_ROW_BOARD][MAX_COL])
{
    for (int row = 1; row < MAX_ROW_BOARD; row++) {
        for (int col = 0; col < MAX_COL; col++)
            board[row][col] = 0;
    }
}

/**
 * @brief Function that invert the state of a cell in the board
 * @param board The board with a size of 24 by 80
 * @param row The row
 * @param col The col
 * @note VGA text mode is 25 by 80 cells large, but here, the first line is infos.
 */
void invert_cell(int board[MAX_ROW_BOARD][MAX_COL], int row, int col)
{
    board[row][col] = (board[row][col] == 0) ? 1 : 0;
}

/**
 * @brief Function that print a cell of the board
 * @param board The board with a size of 24 by 80
 * @param row The row
 * @param col The col
 * @note VGA text mode is 25 by 80 cells large, but here, the first line is infos.
 */
void print_cell(int board[MAX_ROW_BOARD][MAX_COL], int row, int col)
{
    if (board[row][col] == 1)
        print_char(' ', row, col, BLACK_ON_WHITE);
}

/**
 * @brief Function that print the board
 * @param board The board with a size of 24 by 80
 * @note VGA text mode is 25 by 80 cells large, but here, the first line is infos.
 */
void print_board(int board[MAX_ROW_BOARD][MAX_COL])
{
    for (int row = 1; row < MAX_ROW_BOARD; row++) {
        for (int col = 0; col < MAX_COL; col++)
            print_cell(board, row, col);
    }
}

/**
 * @brief Function that launch the GAME OF LIFE
 */
void game(void)
{
    board[9][40] = 1;
    board[9][41] = 1;
    board[9][42] = 1;
    board[10][42] = 1;
    board[11][41] = 1;
    print_board(board);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
