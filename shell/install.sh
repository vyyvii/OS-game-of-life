# OS-Game-Of-Life
# Install file

# Use by the Makefile to istall & configure gcc & ld with i386 32-bytes

	# Configure foldres
mkdir -p ~/opt/cross
mkdir ~/src
export PREFIX="$HOME/opt/cross"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

	# Install binutils
cd ~/src
wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
tar -xf binutils-2.42.tar.xz
cd binutils-2.42
mkdir build && cd build
../configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install

	# Install gcc (& ld/objcopy)
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

#LE CACHEUX, RIVIERE, DEFAUCHY | 2026

