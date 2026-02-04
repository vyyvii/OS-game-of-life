// PRINT STRING C FILE

// Pointeur vers la mémoire vidéo
char *video_memory = (char*) 0xb8000;

// Write a char
void print_char(char c, int col, int row, char attr)
{
    int offset = 2 * (row * 80 + col);

    if (!attr)
        attr = 0x0f; // Blanc sur noir
    video_memory[offset] = c;
    video_memory[offset + 1] = attr;
}

// Write a string
void print_string(char *str)
{
    int i = 0;
    int col = 0, row = 0;

    while (str[i] != '\0') {
        print_char(str[i], col++, row, 0x0f);
        if (col >= 80) {
            col = 0;
            row++;
        }
        i++;
    }
}

// LE CACHEUX, RIVIERE, DEFAUCHY | 2026
