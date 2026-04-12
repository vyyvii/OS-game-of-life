# MAKEFILE FOR OS-GAME OF LIFE

.phony: install_base install_and_config_all compile_boot compile_kernel \
	run_qemu update_repo clean fclean all re

# ─────────────────────────────────────────────────────────────
# NAME
# ─────────────────────────────────────────────────────────────
NAME		= os-image

# ─────────────────────────────────────────────────────────────
# FILES
# ─────────────────────────────────────────────────────────────
KERNEL_SRC = \
	kernel/kernel.c \
	kernel/irq/idt.c \
	kernel/game_of_life/game.c \
	periph/keyboard.c
KERNEL_OBJ = $(KERNEL_SRC:.c=.o)

KERNEL_ASM = \
	kernel/kernel_entry.asm \
	kernel/ports.asm \
	kernel/game_of_life/board.asm \
	kernel/irq/idt_asm.asm \
	kernel/irq/pic.asm \
	periph/screen.asm
KERNEL_ASM_OBJ = $(KERNEL_ASM:.asm=.o)

# ─────────────────────────────────────────────────────────────
# COMPILATION FLAGS & LIBS
# ─────────────────────────────────────────────────────────────
CFLAGS      = -Iinclude
LDFLAGS     =

# ─────────────────────────────────────────────────────────────
# TOOLS
# ─────────────────────────────────────────────────────────────
REMOVE 		= rm -rf
RM_FILES 	= "*.html" "*.css" ".out" "*.o" "*.bin" "*.elf"

export PATH := $(HOME)/opt/cross/bin:$(PATH)

# ─────────────────────────────────────────────────────────────
# CONFIGURATION
# ─────────────────────────────────────────────────────────────
install_base: clear_install
	sudo apt update
	sudo apt install nasm
	sudo apt install qemu-system qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils virt-manager
	sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo

install_and_config_all: install_base
	bash shell/install.sh
	which i386-elf-gcc
	which i386-elf-ld

clear_install:
	sudo apt remove nasm
	sudo rm -rf ~/src
	sudo rm -rf ~/opt/cross

# ─────────────────────────────────────────────────────────────
# COMPILATION
# ─────────────────────────────────────────────────────────────
all: $(NAME)

%.o: %.asm
	nasm -f elf32 $< -o $@

%.o: %.c
	i386-elf-gcc -ffreestanding -m32 -fno-stack-protector -nostdlib $(CFLAGS) -c $< -o $@

compile_boot:
	nasm boot.asm -o boot.bin

compile_kernel: $(KERNEL_OBJ) $(KERNEL_ASM_OBJ)
	i386-elf-ld -m elf_i386 -T kernel/linker.ld $(KERNEL_ASM_OBJ) $(KERNEL_OBJ) -o kernel/kernel.elf
	i386-elf-objcopy -O binary kernel/kernel.elf kernel/kernel.bin

$(NAME): compile_boot compile_kernel
	cat boot.bin kernel/kernel.bin > $(NAME)

# ─────────────────────────────────────────────────────────────
# RUNNING
# ─────────────────────────────────────────────────────────────
run_qemu: all
	qemu-system-i386 -fda $(NAME)


# ─────────────────────────────────────────────────────────────
# CLEANING
# ─────────────────────────────────────────────────────────────
clean:
	for f in $(RM_FILES); do find . -name "$$f" -delete; done

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

#LE CACHEUX, RIVIERE, DEFAUCHY | 2026
