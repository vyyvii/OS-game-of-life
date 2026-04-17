// OS-Game-Of-Life
// KERNEL FILE

#include "kernel.h"

char *video_memory = (char*) 0xb8000;       // The adress of the video memory
int board[MAX_ROW_BOARD][MAX_COL];          // The board for the GAME ((25 - 1) * 80)
cursor_t cursor = { 1, 0, FULL_GRAY };      // The cursor that can move
volatile int go = 0;                        // The indicator to start the game
volatile long speed = DEFAULT_SPEED;          // The size of the hang loop

/**
 * @brief Function offer a way to slow down the game
 */
void sleep(int t)
{
    for (volatile long i = 0; i < t * 10000000; i++);
}

/**
 * @brief Function that launch the GAME OF LIFE
 */
static void game(void)
{
    while (1)
        if (go)
            generation(board);
}

void print_int(int n, int row, int col, int attr)
{
    char buffer[12];
    int i = 0;

    if (n == 0) {
        print_string("0", row, col, attr);
        return;
    }
    while (n > 0) {
        print_char('0', row, col + (i - 1), attr);
        buffer[i++] = (n % 10) + '0';
        n /= 10;
    }
    while (i > 0) {
        char c = buffer[--i];
        print_char(c, row, col - i, attr);
    }
}

void print_up_line(void)
{
    print_string("                                                                                ", 0, 0, WHITE_ON_GRAY);
    print_string("LifeOS", 0, 1, WHITE_ON_GRAY);
    print_string("Q to quit", 0, 9, WHITE_ON_GRAY);
    print_string("Speed:", 0, 20, WHITE_ON_GRAY);
    print_int(speed, 0, 28, WHITE_ON_GRAY);
    print_string("Simulation:", 0, 40, WHITE_ON_GRAY);
    print_string((go) ? "ON" : "OFF", 0, 52, WHITE_ON_GRAY);
    print_string("Defauchy", 0, 71, WHITE_ON_GRAY);
}

/**
 * @brief The main function of the KERNEL
 * @note This function is called by the bootloader by kernel_entry.asm
 */
void kmain(void)
{
    __asm__ volatile ("cli");               // Disable CPU interruption
    idt_init();                             // Initialise the IDT
    reset_screen();                         // Put a black screen
    init_board(board);                      // Initalise the board for the GAME OF LIFE
    print_up_line(),
    print_board(board);
    put_cursor(&cursor);                    // Put the cursor in the middle of the screen
    __asm__ volatile ("sti");               // Enable CPU interruption
    game();                                 // Launch the GAME OF LIFE
    while(1);                               // HANG
}

// DEFAUCHY | 2026
