#!/bin/bash

#set platform name
export PLATFORM_NAME="`uname`"  #local means auto detective by cmake on local machine

#clear compilers
unset CMAKE_C_COMPILER
unset CMAKE_CXX_COMPILER

#set cross compiling compilers and options
#export CMAKE_C_COMPILER="/opt/arm-2012.09/bin/arm-none-linux-gnueabi-gcc-4.7.2"
#export CMAKE_CXX_COMPILER=""

export CMAKE_C_FLAGS="-fPIC"
export CMAKE_CXX_FLAGS="-fPIC"