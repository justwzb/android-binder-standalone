android-binder-standalone
=========================

standalone binder from android with ipc demo including:
1. sample remote calls
2. struct parmters
3. ringbuffer
4. multi-threads callback

### How to build:

```
mkdir out
cd out
source  ../build/envs/envsetup_mt5507.sh  #only work on mt5507 now
cmake ..
make
```

### usage of sidl
```
python tools/sidl/sidl.py xxx.sidl
# see sampleTest and structTest for sidl details, only limited return type and paramters are supported.
```

### Code From:

The source code of binder are copied from ASOP

binder & servicemanager
https://android.googlesource.com/platform/frameworks/native/+/android-4.4.4_r2.0.1

include/kernel 
https://android.googlesource.com/platform/bionic/+/android-4.4.4_r2.0.1

kernel module
https://android.googlesource.com/kernel/common/+log/android-3.10 42df511
