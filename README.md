# OS – Game of Life
Do you want to play the Game of Life? We created an OS where you can only play the Game of Life.

# How to use it with NASM & QEMU ?
sudo apt install nasm
sudo apt install qemu-system qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils virt-manager
nasm -f bin boot.asm -o boot.bin
qemu-system-x86_64 -drive file=boot.bin,format=raw,if=floppy
