# MAKEFILE FOR OS-GAME OF LIFE

.phony: compile_boot compile_kernel run_qemu config_repo clean fclean all re

# ─────────────────────────────────────────────────────────────
# NAME
# ─────────────────────────────────────────────────────────────
NAME		= os-image

# ─────────────────────────────────────────────────────────────
# TOOLS
# ─────────────────────────────────────────────────────────────
REMOVE 		= rm -f -r
RM_FILES 	= "*.html" "*.css" "*.log" ".out" "*.o" "*.bin" ".elf"


# ─────────────────────────────────────────────────────────────
# CONFIGURATION
# ─────────────────────────────────────────────────────────────
install_dependencies:
	sudo apt update
	sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo

install_gcc:
	cd ~/src
	wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.xz
	tar -xf gcc-13.2.0.tar.xz
	cd gcc-13.2.0

	./contrib/download_prerequisites
	mkdir build && cd build
	../configure --target=$TARGET --prefix=$PREFIX \
				--disable-nls --enable-languages=c \
				--without-headers
	make all-gcc -j$(nproc)
	make all-target-libgcc -j$(nproc)
	make install-gcc
	make install-target-libgcc

install_binutils:
	cd ~/src
	wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
	tar -xf binutils-2.42.tar.xz
	cd binutils-2.42

	mkdir build && cd build
	../configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
	make -j$(nproc)
	make install

config_repo:
	mkdir -p ~/opt/cross
	mkdir ~/src
	export PREFIX="$HOME/opt/cross"
	export TARGET=i386-elf
	export PATH="$PREFIX/bin:$PATH"

update_repo:
	export PREFIX="$HOME/opt/cross"
	export TARGET=i386-elf
	export PATH="$PREFIX/bin:$PATH"

install_and_config_all: install_dependencies config_repo install_binutils install_gcc
	which i386-elf-gcc
	which i386-elf-ld

# ─────────────────────────────────────────────────────────────
# COMPILATION
# ─────────────────────────────────────────────────────────────
all: update_repo $(NAME)

compile_boot:
	nasm boot.asm -o boot.bin

compile_kernel:
	nasm -f elf32 kernel/kernel_entry.asm -o kernel/kernel_entry.o
	i386-elf-gcc -ffreestanding -m32 -fno-stack-protector -nostdlib -c kernel/kernel.c -o kernel/kernel.o
	i386-elf-ld -m elf_i386 -T kernel/linker.ld kernel/kernel_entry.o kernel/kernel.o -o kernel/kernel.elf
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
