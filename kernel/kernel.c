// ===============================
// KERNEL PRINCIPAL EN C
// ===============================

#include "../print_pm.asm"

// Pointeur vers la mémoire vidéo
char *video_memory = (char*) 0xb8000;

// Fonction pour écrire un caractère
void print_char(char c, int col, int row, char attr)
{
    int offset = 2 * (row * 80 + col);

    if (!attr)
        attr = 0x0f; // Blanc sur noir
    video_memory[offset] = c;
    video_memory[offset + 1] = attr;
}

// Fonction pour écrire une string
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

// Point d'entrée du kernel
void main(void) {
    // Effacer l'écran
    for (int i = 0; i < 80 * 25 * 2; i++)
        video_memory[i] = 0;
    // Afficher message
    print_string("Kernel C loaded successfully!");
    print_char('X', 10, 2, 0x4f); // 'X' rouge sur blanc
    // Boucle infinie
    while(1);
}
