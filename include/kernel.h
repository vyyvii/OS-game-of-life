// OS-Game-Of-Life
// KERNEL HEADER

#ifndef KERNEL_H
    #define KERNEL_H

    // ATTRIBUTES
    #define WHITE_ON_BLACK 0x0f
    #define BLACK_ON_WHITE 0xf0
    #define WHITE_ON_GRAY 0x8f
    #define FULL_GRAY 0x88

    // ROWS & COLS
    #define MAX_ROW 25
    #define MAX_ROW_BOARD 24
    #define MAX_COL 80

    // SCANCODES & SPECIALS REGS
    #define SCANCODE_REG 0x60
    #define SCANCODE_EXT 0xe0
    #define PIC_MASTER 0x20
    #define VIDEO_MEMORY 0xB8000

    // ARROWS SCANCODES
    #define UP_ARROW 0x48
    #define DOWN_ARROW 0x50
    #define LEFT_ARROW 0x4b
    #define RIGHT_ARROW 0x4d

    // SPEED
    #define DEFAULT_SPEED 90
    #define MIN_SPEED 0
    #define MAX_SPEED 100
    #define BASE_PIT_FREQ 1193180
    #define BASE_FREQ 100

    // ELSE
    #define QUIT_QEMU 0x604
    #define BACKSPACE 0x0E
    #define ENTER 0x1C
    #define MAX_INT_SIZE 12

    #include "types.h"

// TYPEDEFS & STRUCTS
typedef struct cursor_s {
    int row;
    int col;
    int color;
} cursor_t;
    // CURSOR STRUCTURE CALLABLE ACROSS FILES

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attr;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// EXTERN
extern char *video_memory;                  // The adress of the video memory
extern int board[MAX_ROW_BOARD][MAX_COL];   // The board for the GAME ((25 - 1) * 80)
extern cursor_t cursor;                     // The cursor that can move
extern volatile int go;                     // The indicator to start the game or to stop it
extern volatile long speed;                 // The size of the hang loop
extern volatile uint32_t ticks;             // Ticks (IRQ0)

// FUNCTIONS
    // IDT (interrupt descriptor table)
void idt_init(void);

    // PIC (programmable interrupt transistor)
void pic_remap(void);

    // AUX
void print_int(int n, int row, int col, int attr);
void print_up_line(void);
int abs(int nb);

    // PORTS
void outb(uint16_t port, uint8_t data);
void outw(uint16_t port, uint16_t data);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

    // SCREEN
void print_char(char c, int row, int col, char attr);
void print_string(char *str, int row, int col, int color);
void reset_screen(void);
void put_cursor(cursor_t *cursor);

    // KEYBOARD
void keyboard_handler(void);

    // TIMER
void timer_handler(void);
void init_timer(uint32_t freq);
void sleep(uint32_t ms);

    // GAME
        // GENERATION
void randomize_board(int board[MAX_ROW_BOARD][MAX_COL], int pct_cpt);
uint32_t rand(void);

        // BOARD
void print_cell(int board[MAX_ROW_BOARD][MAX_COL], int row, int col);
void print_board(int board[MAX_ROW_BOARD][MAX_COL]);
void init_board(int board[MAX_ROW_BOARD][MAX_COL]);

        // SIMULATION
void generation(int board[MAX_ROW_BOARD][MAX_COL]);

#endif

// DEFAUCHY | 2026
