// ===============================
// KERNEL PRINCIPAL EN C
// ===============================

void kmain(void)
{
    char *vga = (char*)0xb8000;

    vga[0] = 'O';
    vga[1] = 0x0f;

    vga[2] = 'S';
    vga[3] = 0x0f;

    vga[4] = '!';
    vga[5] = 0x0f;

    while (1);
}

