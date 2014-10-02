#!/bin/bash

#set platform name
export PLATFORM_NAME="`uname`"  #local means auto detective by cmake on local machine

#clear compilers
unset CMAKE_C_COMPILER
unset CMAKE_CXX_COMPILER
unset CMAKE_C_FLAGS
unset CMAKE_CXX_FLAGS

#set cross compiling compilers and options
#export CMAKE_C_COMPILER="/opt/arm-2012.09/bin/arm-none-linux-gnueabi-gcc-4.7.2"
#export CMAKE_CXX_COMPILER=""

#usually all these should be defined
#-DHAVE_SYS_UIO_H has bits/uio.h
#-DHAVE_PTHREADS has pthread.h
#-DHAVE_ENDIAN_H has endian.h
#-DHAVE_OFF64_T has off64_t
#-DHAVE_POSIX_FILEMAP has mmap
#-DOS_PATH_SEPARATOR='/'
#-DANDROID_SMP=1
export CMAKE_C_FLAGS="-DHAVE_SYS_UIO_H -DHAVE_PTHREADS -DHAVE_ENDIAN_H -DHAVE_OFF64_T -DHAVE_POSIX_FILEMAP -DOS_PATH_SEPARATOR=\'/\' -DANDROID_SMP=1"
export CMAKE_CXX_FLAGS="-DHAVE_SYS_UIO_H -DHAVE_PTHREADS -DHAVE_ENDIAN_H -DHAVE_OFF64_T -DHAVE_POSIX_FILEMAP -DOS_PATH_SEPARATOR=\'/\' -DANDROID_SMP=1"

#arm,mips,x86
export CMAKE_TARGET_ARCH="x86"
