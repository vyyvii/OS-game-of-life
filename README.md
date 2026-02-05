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

## How do you compiling and Running own OS

If you want install gcc for a better Compilling you can with this line :
>[!WARNING]
> You must acces root for this installation
```
Make install_and_config_all
```

And after you can Compiling and running like this
```
make run_qemu
```
