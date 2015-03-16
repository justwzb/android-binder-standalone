running linux in qemus aarch64 system emulation
=========================
Tested on Ubuntu 14.04.1 LTS.

Ref: http://www.bennee.com/~alex/blog/2014/05/09/running-linux-in-qemus-aarch64-system-emulation-mode/

### build qemu with aarch64 support

```
sudo apt-get build-dep qemu
wget http://wiki.qemu-project.org/download/qemu-2.2.1.tar.bz2
tar -jxvf qemu-2.2.1.tar.bz2
cd qemu-2.2.1
./configure --target-list=aarch64-softmmu
make
cd ..
```

### test qemu with aarch64 support
```
wget http://people.linaro.org/~alex.bennee/images/aarch64-linux-3.15rc2-buildroot.img
qemu-2.2.1/aarch64-softmmu/qemu-system-aarch64 -machine virt -cpu cortex-a57 -machine type=virt -nographic -smp 1 -m 2048 -kernel aarch64-linux-3.15rc2-buildroot.img --append "console=ttyAMA0"
```

### install aarch64 toolchain
```
sudo apt-get install gcc-aarch64-linux-gnu
```


### build rootfs
```
wget http://buildroot.net/downloads/buildroot-2015.02.tar.gz
tar -zxvf buildroot-2015.02.tar.gz
cd buildroot-2015.02
make menuconfig
make
cd ..
```

configuration:

* Target Options -> Target Architecture(AArch64)
* Toolchain -> Toolchain type (External toolchain)
* Toolchain -> Toolchain (Linaro AArch64 14.02)
* System configuration -> Run a getty (login prompt) after boot (BR2_TARGET_GENERIC_GETTY)
* System configuration -> getty options -> TTY Port (ttyAMA0) (BR2_TARGET_GENERIC_GETTY_PORT)
* Target Packages -> Show packages that are also provided by busybox (BR2_PACKAGE_BUSYBOX_SHOW_OTHERS)
* Filesystem images -> cpio the root filesystem (for use as an initial RAM filesystem) (BR2_TARGET_ROOTFS_CPIO)

Here is the [config](buildroot_config) that I used. 


### Building kernel
```
wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.10.71.tar.xz
tar -xvf linux-3.10.71.tar.xz
cd linux-3.10.71/
make defconfig ARCH=arm64
make menuconfig ARCH=arm64
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
cd ..
```

configuration:

 * CONFIG_CROSS_COMPILE="aarch64-linux-gnu-"
 * CONFIG_VIRTIO=y  #CONFIG_NET_9P_VIRTIO need it
 * CONFIG_NET_9P=y # needed for virtfs mount
 * CONFIG_NET_9P_VIRTIO=y
 * CONFIG_9P_FS=y

Here is the [config](aarch64_qemu_config) that I used. 

### Run Test
```
mkdir swap
./qemu-2.2.1/aarch64-softmmu/qemu-system-aarch64 -machine virt -cpu cortex-a57 -machine type=virt -nographic -smp 1 -m 2048 -kernel linux-3.10.71/arch/arm64/boot/Image -initrd ./buildroot-2015.02/output/images/rootfs.cpio --append "console=ttyAMA0" -fsdev local,id=r,path=./swap/,security_model=none -device virtio-9p-device,fsdev=r,mount_tag=r
```

### Run in qemu Linux
```
mount -t 9p -o trans=virtio r /mnt
```
