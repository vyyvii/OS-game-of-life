// OS-Game-Of-Life
// FUNCTIONS FILE

#include "kernel.h"

static void init_board(int board[25][80])
{
    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 80; col++)
            board[row][col] = 0;
    }
}

void invert_cell(int board[25][80], int row, int col)
{
    board[row][col] = (board[row][col] == 0) ? 1 : 0;
}

void print_cell(int board[25][80], int row, int col)
{
    if (board[row][col] == 1)
        print_char(' ', row, col, BLACK_ON_WHITE);
}

void print_board(int board[25][80])
{
    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 80; col++)
            print_cell(board, row, col);
    }
}

void game(void)
{
    int board[25][80];

    init_board(board);
    board[9][40] = 1;
    board[9][41] = 1;
    board[9][42] = 1;
    board[10][42] = 1;
    board[11][41] = 1;
    print_board(board);
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
