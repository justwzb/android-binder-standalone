android-binder-standalone
=========================

standalone binder from android with ipc demo

### How to build:

```
mkdir out
cd out
source  ../build/envs/envsetup_local.sh 
cmake ..
make
```

### Code From:

The source code of binder are copied from ASOP

binder & servicemanager
https://android.googlesource.com/platform/frameworks/native/+/android-4.4.4_r2.0.1

kernel module
https://android.googlesource.com/kernel/common/+log/android-3.10
42df511