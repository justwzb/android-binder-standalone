android-binder-standalone
=========================

standalone binder from android with ipc demo including:

* sample remote calls
* struct parmters
* ringbuffer without copy
* multi-threads callbacks

### How to build:

```
mkdir out
cd out
source  ../build/envs/envsetup_mt5507.sh  #only work on mt5507 now
cmake ..
make
```

### Usage of sidl
```
python tools/sidl/sidl.py xxx.sidl
# see sampleTest and structTest for sidl details, only limited return type and paramters are supported.
```

### Make a test environment

aarch64 as an example. 

http://www.bennee.com/~alex/blog/2014/05/09/running-linux-in-qemus-aarch64-system-emulation-mode/

Below is the code version that I used to test.

```
git clone git://git.qemu.org/qemu.git qemu.git
commit 3539bbb93e944ffde31c61c369ea9eedcc5697a6
Merge: 576a94d 47cbe50
Author: Peter Maydell <peter.maydell@linaro.org>
Date:   Wed Mar 4 14:37:31 2015 +0000
```

http://buildroot.net/downloads/buildroot-2015.02.tar.gz

https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.10.71.tar.xz
```
make defconfig ARCH=arm64
make  ARCH=arm64 CROSS_COMPILE=arm-none-linux-gnueabi-
```



### Code From:

The source code of binder are copied from AOSP

binder & servicemanager
https://android.googlesource.com/platform/frameworks/native/+/android-4.4.4_r2.0.1

include/kernel 
https://android.googlesource.com/platform/bionic/+/android-4.4.4_r2.0.1

kernel module
https://android.googlesource.com/kernel/common/+log/android-3.10 42df511



### TODO List:

 * removing bionic in this branch!       OK
 * Run on 64bits platform
