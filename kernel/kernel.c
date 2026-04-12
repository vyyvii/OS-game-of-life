// OS-Game-Of-Life
// KERNEL FILE

#include "kernel.h"

char *video_memory = (char*) 0xb8000;       // The adress of the video memory
int board[MAX_ROW_BOARD][MAX_COL];          // The board for the GAME ((25 - 1) * 80)
cursor_t cursor = { 1, 0, FULL_GRAY };    // The cursor that can move

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
    put_cursor(&cursor);                    // Put the cursor in the middle of the screen
    print_string(" LifeOS | Kernel x86 Protected Mode", 0, 0, WHITE_ON_GRAY);
    print_string("                           Defauchy, Riviere ", 0, 35, WHITE_ON_GRAY);
    __asm__ volatile ("sti");               // Enable CPU interruption
    game();                                 // Launch the GAME OF LIFE
    while(1);                               // HANG
}

// DEFAUCHY, RIVIERE | 2026
