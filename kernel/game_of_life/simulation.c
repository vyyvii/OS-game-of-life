// OS-Game-Of-Life
// SIMULATION FILE

#include "kernel.h"

/**
 * @brief Compute and display the next generation of the Game of Life.
 * This function:
 * 1. Computes the number of neighbors for each cell.
 * 2. Applies the Game of Life rules to update the board.
 * 3. Prints the updated board.
 * 4. Restores the cursor position.
 * 5. Waits for a short delay to control simulation speed.
 * @param board The game board (2D array of cells).
 */
void simulation(int board[MAX_ROW_BOARD][MAX_COL])
{
    int matrice[MAX_ROW_BOARD][MAX_COL];

    for (int i = 0; i < MAX_ROW_BOARD; i++)
        for (int j = 0; j < MAX_COL; j++)
            matrice[i][j] = simule_one_cell(board, i, j);
    for (int i = 0; i < MAX_ROW_BOARD; i++)
        for (int j = 0; j < MAX_COL; j++)
            board[i][j] = new_state(matrice[i][j], board[i][j]);
    print_board(board);
    put_cursor(&cursor);
    sleep((uint32_t)abs(speed - 100));
}

// DEFAUCHY - RIVIERE | 2026
