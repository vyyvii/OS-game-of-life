// OS-Game-Of-Life
// SIMULATION FILE

#include "kernel.h"

static uint32_t seed = 123456;

/**
 * @brief Fill the Game of Life board with random values.
 * Initializes each cell of the board with a pseudo-random state
 * (alive or dead) based on a given percentage.
 * For each cell, a random value between 0 and 99 is generated.
 * If this value is lower than @p pct, the cell is set to alive (1),
 * otherwise it is set to dead (0).
 * @param board The game board (2D array of cells).
 * @param pct Percentage of alive cells (0–100).
 * @note A lower percentage creates sparse patterns (more interesting evolution),
 * while a higher percentage may lead to overcrowding and quick stabilization.
 * @warning Requires a properly initialized pseudo-random generator.
 */
void randomize_board(int board[MAX_ROW_BOARD][MAX_COL], int pct)
{
    if (pct < 0 || pct > 100)
        pct = 25;
    for (int i = 0; i < MAX_ROW_BOARD; i++)
        for (int j = 0; j < MAX_COL; j++)
            board[i][j] = (rand() % 100 < pct);
}

/**
 * @brief Generate a pseudo-random number using a linear congruential generator.
 * Updates and returns a pseudo-random value based on a global or static seed.
 * The current implementation mixes the previous seed with the global `ticks`
 * counter to introduce variability over time.
 * @return uint32_t A pseudo-random 32-bit unsigned integer.
 * @note The quality of randomness depends on the seed initialization and update.
 * For better variability, the seed should be initialized once (e.g., with `ticks`)
 * and stored persistently (e.g., as a static or global variable).
 * @warning In its current form, if `seed` is not persistent (static/global),
 * the function will always return the same value, resulting in
 * non-random behavior.
 */
uint32_t rand(void)
{
    seed = seed * 1103515245 + 12345 + ticks;

    return seed;
}

// DEFAUCHY | 2026
