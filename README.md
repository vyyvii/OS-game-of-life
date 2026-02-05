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