# OS – Game of Life
Do you want to play the Game of Life? We created an OS where you can only play the Game of Life.

# How to use it with NASM & QEMU ?

First make sure nasm is installed, for ubuntu you can use :
```bash
sudo apt install nasm
```

You will then need to install qemu and a few other dependencies :
```bash
sudo apt install qemu-system qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils virt-manager
```

## Compiling and running

You will need to compile the bootloader, to do so you can type :
```bash
nasm -f bin boot.asm -o boot.bin
```

You can now run the bootloader using :
```bash
qemu-system-x86_64 -drive file=boot.bin,format=raw,if=floppy
```

## How do you compiling kernel ? and How do you running this OS

If you use Qemu you can use this :
```
gcc -ffreestanding -m32 -fno-stack-protector -nostdlib -c kernel/kernel.c -o kernel/kernel.o
ld -m elf_i386 -T kernel/linker.ld kernel/kernel.o -o kernel/kernel.elf
objcopy -O binary kernel/kernel.elf kernel/kernel.bin
```

After compiling and create kernel you must concatanate and run like this :
```
cat boot.bin kernel/kernel.bin > os-image.bin
qemu-system-i386 -fda os-image.bin
```

If you want install gcc for a better Compilling you can with this line :
```
export TARGET=x86_64-elf
export PREFIX=/opt/cross
export PATH="$PREFIX/bin:$PATH"
sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo
wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
tar -xf binutils-2.42.tar.xz
mkdir build-binutils
cd build-binutils

../binutils-2.42/configure \
  --target=$TARGET \
  --prefix=$PREFIX \
  --with-sysroot \
  --disable-nls \
  --disable-werror

make -j$(nproc)
sudo make install
cd ..
wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.xz
tar -xf gcc-13.2.0.tar.xz
cd gcc-13.2.0
./contrib/download_prerequisites
mkdir build-gcc
cd build-gcc

../configure \
  --target=$TARGET \
  --prefix=$PREFIX \
  --disable-nls \
  --enable-languages=c \
  --without-headers

make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)
sudo make install-gcc
sudo make install-target-libgcc
```

And after you can Compiling like this :
```
x86_64-elf-gcc -ffreestanding -m32 -fno-stack-protector -nostdlib -c kernel/kernel.c -o kernel/kernel.o
x86_64-elf-ld -m elf_i386 -T kernel/linker.ld kernel/kernel.o -o kernel/kernel.elf
x86_64-elf-objcopy -O binary kernel/kernel.elf kernel/kernel.bin
```
you must too concatanate and run like this :

```
cat boot.bin kernel/kernel.bin > os-image.bin
qemu-system-i386 -fda os-image.bin
```