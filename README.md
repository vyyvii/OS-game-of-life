# OS – Game of Life
Do you want to play the Game of Life? We've created an OS where you can only play the Game of Life.

We present you: **LifeOS**

## How to install everything in order to have the tools useful to create the os-image?

First you have to install nasm & qemu & gcc/ld/objcopy for i386 32-bit.\
We've created a rule in the makefile to install everything and to configure correctly the packages.
>[!WARNING]
> You must access **root** for this installation

```bash
make install_and_config_all
```

>[!NOTE]
> This installation might be very long, just wait!

## Troubleshooting for installation

If the installations fails, try the following:
1. Verify your internet connection
2. Do: make clear_install && make install_base && make install_and_config_all
3. Run this in your terminal:
```bash
make clear_install
export PREFIX="$HOME/opt/cross"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
make install_and_config_all
```
4. Ask ChatGPT or pray

## How do you compile & run your own OS

>[!WARNING]
> The following steps need **all** tools to be installed !

Compile everything & run qemu:
```bash
make run_qemu
```

Compile everything:
```bash
make all
```

Clear & compile everything:
```bash
make re
```

> [!WARNING]
> **DON'T RUN IT ON YOUR LAPTOP** WITHOUT AN HYPERVISOR!\
> You can **kill your disk or your CPU**!\
> ***Be careful!***

## Breakdown of the Makefile rules

>[!NOTE]
> Each block explain how the rule works and what it call

The Makefile for this project contains the following rules:
- install_base:

        Update Linux
        Install "nasm"
        Install "qemu"
        Install some dependencies

- install_and_config_all: install_base

        Call install_base rule (see install_base).

        Execute the shell file install.sh (./shell/install.sh).
        ^ This file install & configure gcc & ld
                for an i386 32-bit architecture.

        Verify if i386-elf-gcc & i386-elf-ld are installed.

- clear_install:

        Remove all of the installations made previously.
        The folders "~/src" & "~/opt/cross" are deleted.

- all: $(NAME)

        Call the principal rule to create the os-image file (see $(NAME)).

- %.o: %.asm

        Compile all of the assemblers files with nasm in elf32 format.

- %.o: %.c

        Compile all of the c files with i386-elf-gcc.

- compile_boot:

        Compile the bootloader file (boot.asm) in a binary (boot.bin).

- compile_kernel:

        Compile the kernel.
        For that, it compiles all the c (.c) files & assemblers (.asm) files into objects (.o) files with the $(KERNEL_OBJ) $(KERNEL_ASM_OBJ) rules.
        Then it links everythings with the linker.ld file.
        Finally, it transform the elf file (kernel.elf) to a binary file (kernel.bin).

        This ensures that the kernel is linked whith the kernel entry.

- $(NAME): compile_boot compile_kernel

        Main rule of the file. It compiles everything to os-image.
        Call compile_boot & compile_kernel rules (see compile_boot & compile_kernel).
        The boot_sector binary & the kernel binary are put together in a new binary.

        The kernel is at 0x1000 and the boot sector 0x0 & is 512 bytes long (terminated by 0x55AA).

- run_qemu: all

        Call all rule (see all).
        Run qemu with our new os-image.

- clean:

        Remove all files ending with:
        .html, .css, .log, .out, .o, .bin or .elf

- fclean: clean

        Call clean rule (see clean).
        Remove os-image.

- re: fclean all

        Call fclean & all rules (see fclean & all).

# Langages

- `asm`
- `c`
- `makefile`
- `shell`
- `linker script`

# Resources

_"Writing a Simple Operating System — from Scratch"_ by Nick Blundell\
School of Computer Science, University of Birmingham, UK\
December 2, 2010\
Copyright c 2009–2010 Nick Blundell

_"vas-y, viens, on recode Windows de zéro"_ by V2F\
youtube.com\
October 10, 2024

_"Building an OS - 1 - Hello world"_ by nanobyte\
youtube.com\
January 27, 2019

_"Le Jeu de la Vie."_ by EGO\
youtube.com\
April 20, 2024

_ghaiklor-os-gcc_ by Eugene Obrezkov\
https://github.com/ghaiklor/ghaiklor-os-gcc\
Copyright (c) 2016 Eugene Obrezkov

_nanobyte_os_ by nanobyte\
https://github.com/nanobyte-dev/nanobyte_os

_Wiki OSdev_ by MediaWiki\
mediawiki.org\
https://wiki.osdev.org/Expanded_Main_Page

>[!NOTE]
> This are resources, not models

# Contributors

Adrien **Le Cacheux**\
Nicolas **Rivière**\
Victor **Defauchy**

_LifeOS_\
For  _OS-Game-Of-Life_  Project | 2026
