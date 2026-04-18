// OS-Game-Of-Life
// KERNEL FILE

#include "kernel.h"

/**
 * @brief Compute the next state of a cell based on its neighbors.
 *
 * Applies Conway's Game of Life rules:
 * - A dead cell becomes alive if it has exactly 3 neighbors.
 * - A living cell survives if it has 2 or 3 neighbors.
 * - Otherwise, the cell dies or remains dead.
 *
 * @param neighbors Number of alive neighboring cells.
 * @param state Current state of the cell (0 = dead, 1 = alive).
 * @return int The new state of the cell (0 = dead, 1 = alive).
 */
static int new_state(int neighbors, int state)
{
    if (state == 0 && neighbors == 3)
        return 1;
    if (state == 1)
        return (neighbors < 2 || neighbors > 3) ? 0 : 1;
    return 0;
}

/**
 * @brief Count the number of alive neighbors around a specific cell.
 *
 * Iterates over the 8 surrounding cells of position (i, j),
 * ensuring boundaries are respected and excluding the cell itself.
 *
 * @param board The game board (2D array of cells).
 * @param i Row index of the target cell.
 * @param j Column index of the target cell.
 * @return int Number of alive neighboring cells.
 */
static int simule_one_cell(int board[MAX_ROW_BOARD][MAX_COL], int i, int j)
{
    int cpt = 0;

    for (int ii = i - 1; ii <= i + 1; ii++) {
        if (ii < 0 || ii >= MAX_ROW_BOARD)
            continue;
        for (int jj = j - 1; jj <= j + 1; jj++) {
            if (jj < 0 || jj >= MAX_COL || (ii == i && jj == j))
                continue;
            cpt = (board[ii][jj] == 1) ? cpt + 1 : cpt;
        }
    }
    return cpt;
}

/**
 * @brief Compute and display the next generation of the Game of Life.
 *
 * This function:
 * 1. Computes the number of neighbors for each cell.
 * 2. Applies the Game of Life rules to update the board.
 * 3. Prints the updated board.
 * 4. Restores the cursor position.
 * 5. Waits for a short delay to control simulation speed.
 *
 * @param board The game board (2D array of cells).
 */
void generation(int board[MAX_ROW_BOARD][MAX_COL])
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
