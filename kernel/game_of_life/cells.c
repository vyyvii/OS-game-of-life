// OS-Game-Of-Life
// KERNEL FILE

#include "kernel.h"

static int new_state(int neighbors, int state)
{
    if (state == 0 && neighbors == 3)
        return 1;
    if (state == 1)
        return (neighbors < 2 || neighbors > 3) ? 0 : 1;
    return 0;
}

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
    sleep(speed);
}
