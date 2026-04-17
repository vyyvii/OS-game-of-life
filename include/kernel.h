// OS-Game-Of-Life
// KERNEL HEADER

#ifndef KERNEL_H
    #define KERNEL_H

    #define WHITE_ON_BLACK 0x0f
    #define BLACK_ON_WHITE 0xf0
    #define WHITE_ON_GRAY 0x8f
    #define FULL_GRAY 0x88

    #define MAX_ROW 25
    #define MAX_ROW_BOARD 24
    #define MAX_COL 80

    #define SCANCODE_REG 0x60
    #define SCANCODE_EXT 0xe0

    #define UP_ARROW 0x48
    #define DOWN_ARROW 0x50
    #define LEFT_ARROW 0x4b
    #define RIGHT_ARROW 0x4d

    #define QUIT_QEMU 0x604
    #define BACKSPACE 0x0E
    #define ENTER 0x1C
    #define SC_MAX 5

    #define DEFAULT_SPEED 10
    #define MIN_SPEED 20
    #define MAX_SPEED 1

    #include "types.h"

// TYPEDEFS & STRUCTS
typedef struct cursor_s {
    int row;
    int col;
    int color;
} cursor_t;

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
extern char *video_memory;
extern int board[MAX_ROW_BOARD][MAX_COL];
extern cursor_t cursor;
extern volatile int go;
extern volatile long speed;

// IDT (interrupt descriptor table)
void idt_init(void);

// PIC (programmable interrupt transistor)
void pic_remap(void);

// FUNCTIONS
int my_strlen(char str[]);
void append(char str[], char n);
void unappend(char str[]);

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

// GAME
void init_board(int board[MAX_ROW_BOARD][MAX_COL]);
void print_cell(int board[MAX_ROW_BOARD][MAX_COL], int row, int col);
void print_board(int board[MAX_ROW_BOARD][MAX_COL]);
void generation(int board[MAX_ROW_BOARD][MAX_COL]);
void sleep(int t);
void print_int(int n, int row, int col, int attr);
void print_up_line(void);

#endif

// DEFAUCHY | 2026
