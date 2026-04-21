# MAKEFILE FOR OS-GAME OF LIFE

# ─────────────────────────────────────────────────────────────
# NAME
# ─────────────────────────────────────────────────────────────
NAME			= 	LifeOS-image

# ─────────────────────────────────────────────────────────────
# FILES
# ─────────────────────────────────────────────────────────────
KERNEL_SRC 		= \
					kernel/kernel.c \
					kernel/aux.c \
					kernel/timer.c \
					kernel/irq/idt.c \
					periph/keyboard.c \
					kernel/game_of_life/generation.c \
					kernel/game_of_life/simulation.c
KERNEL_OBJ 		= 	$(KERNEL_SRC:.c=.o)

KERNEL_ASM 		= \
					kernel/kernel_entry.asm \
					kernel/ports.asm \
					kernel/game_of_life/board_init.asm \
					kernel/game_of_life/board_printing.asm \
					kernel/irq/idt_asm.asm \
					kernel/irq/pic.asm \
					periph/screen.asm \
					kernel/multiboot.asm
KERNEL_ASM_OBJ 	= 	$(KERNEL_ASM:.asm=.o)

BOOT 		   	= 	boot.asm
BOOT_BIN		=	boot.bin
LINKER			=	kernel/linker.ld
KERNEL_BIN		= 	kernel/kernel.bin

# ─────────────────────────────────────────────────────────────
# COMPILER & COMPILATION FLAGS
# ─────────────────────────────────────────────────────────────
CC			= 		i386-elf-gcc
CFLAGS      = 		-ffreestanding -m32 -fno-stack-protector -nostdlib -Iinclude

NASM		= 		nasm
NASM_FLAGS	=	 	-f elf32

# ─────────────────────────────────────────────────────────────
#  HYPERVISOR & OTHERS
# ─────────────────────────────────────────────────────────────
QEMU 	    =		qemu-system-i386
QEMU_FLAGS 	=		-fda

OBJCOPY 	=		i386-elf-objcopy
OBJCP_FLAGS =		-O binary kernel/kernel.elf

LD			=		i386-elf-ld
LD_FLAGS	=		-m elf_i386 -o kernel/kernel.elf

# ─────────────────────────────────────────────────────────────
# TOOLS
# ─────────────────────────────────────────────────────────────
INSTALL 	= 		sudo apt

REMOVE 		= 		rm -rf
RM_FILES 	= 		"*.out" "*.o" "*.bin" "*.elf"

export PATH := $(HOME)/opt/cross/bin:$(PATH)

# ─────────────────────────────────────────────────────────────
# CONFIGURATION
# ─────────────────────────────────────────────────────────────
install_base: clear_install
	$(INSTALL) update
	$(INSTALL) install nasm
	$(INSTALL) install qemu-system qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils virt-manager
	$(INSTALL) install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo

install_and_config_all: install_base
	bash shell/install.sh
	which $(CC)
	which $(LD)

clear_install:
	$(INSTALL) remove nasm
	sudo $(REMOVE) ~/src
	sudo $(REMOVE) ~/opt/cross

# ─────────────────────────────────────────────────────────────
# COMPILATION
# ─────────────────────────────────────────────────────────────
all: $(NAME)

%.o: %.asm
	$(NASM) $(NASM_FLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

compile_boot:
	$(NASM) $(BOOT) -o $(BOOT_BIN)

compile_kernel: $(KERNEL_OBJ) $(KERNEL_ASM_OBJ)
	$(LD) $(LD_FLAGS) -T $(LINKER) $(KERNEL_ASM_OBJ) $(KERNEL_OBJ)
	$(OBJCOPY) $(OBJCP_FLAGS) $(KERNEL_BIN)

$(NAME): compile_boot compile_kernel
	cat $(BOOT_BIN) $(KERNEL_BIN) > $(NAME)

# ─────────────────────────────────────────────────────────────
# RUNNING
# ─────────────────────────────────────────────────────────────
run_qemu: all
	$(QEMU) $(QEMU_FLAGS) $(NAME)

# ─────────────────────────────────────────────────────────────
# CLEANING
# ─────────────────────────────────────────────────────────────
clean:
	for f in $(RM_FILES); do find . -name "$$f" -delete; done

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

# ─────────────────────────────────────────────────────────────
# PHONY TARGETS
# ─────────────────────────────────────────────────────────────
.phony: install_base install_and_config_all compile_boot compile_kernel \
	run_qemu update_repo clean fclean all re

# DEFAUCHY | 2026
