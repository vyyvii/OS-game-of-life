// OS-Game-Of-Life
// KERNEL FILE

#include "kernel.h"

// EXTERN
char *video_memory = (char*) 0xb8000;       // The adress of the video memory
int board[MAX_ROW_BOARD][MAX_COL];          // The board for the GAME ((25 - 1) * 80)
cursor_t cursor = { 1, 0, FULL_GRAY };      // The cursor that can move
volatile int go = 0;                        // The indicator to start the game or to stop it
volatile long speed = DEFAULT_SPEED;        // The size of the hang loop
volatile uint32_t ticks = 0;                // Ticks (IRQ0)

/**
 * @brief Function that launch the GAME OF LIFE
 */
static void game(void)
{
    while (1)
        if (go)
            generation(board);
}

/**
 * @brief The main function of the KERNEL
 * @note This function is called by the bootloader by kernel_entry.asm
 */
void kmain(void)
{
    __asm__ volatile ("cli");               // Disable CPU interruption
    idt_init();                             // Initialise the IDT
    init_timer(BASE_FREQ);                  // Initialise the ticks (IRQ0) timer at 100Hz
    reset_screen();                         // Put a black screen
    init_board(board);                      // Initalise the board for the GAME OF LIFE
    print_up_line(),                        // Print the upper line (not in the board)
    print_board(board);                     // Print the board
    put_cursor(&cursor);                    // Put the cursor in the middle of the screen
    __asm__ volatile ("sti");               // Enable CPU interruption
    game();                                 // Launch the GAME OF LIFE
    while(1);                               // HANG
}

// DEFAUCHY | 2026
