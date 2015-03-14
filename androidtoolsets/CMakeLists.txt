FIND_PACKAGE(AndroidToolsets REQUIRED)
INCLUDE_DIRECTORIES(${AndroidToolsets_INCLUDE_DIR})

#liblog
SET(LIB_Log_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/liblog/logd_write.c
    ${CMAKE_CURRENT_SOURCE_DIR}/liblog/fake_log_device.c
)
ADD_DEFINITIONS(-DFAKE_LOG_DEVICE=1)

#libutils
SET(LIB_Utils_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/String8.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/String16.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/RefBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Unicode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/VectorImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Timers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Threads.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/misc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/SharedBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Static.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/SystemClock.cpp
    #on android, below files are only added on device.
    #${CMAKE_CURRENT_SOURCE_DIR}/libutils/Trace.cpp
)

#libcutils
SET(LIB_Cutils_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/atomic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/process_name.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/sched_policy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/threads.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/native_handle.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/hashmap.c

    #for ashmem, device only on android, but kernel module needed
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/ashmem-dev.c

    #on android, below files are only added on device.
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/android_reboot.c
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/debugger.c
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/klog.c
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/partition_utils.c
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/properties.c
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/qtaguid.c
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/trace.c
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/uevent.c

    #TODO arch-arm/memset32.S etc
    #${CMAKE_CURRENT_SOURCE_DIR}/libcutils/arch-arm/memset32.S
)

#bionic, only very limited needed c files are added
SET(LIB_Bionic_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/bionic/strlcpy.c
)

ADD_LIBRARY(AndroidToolsets STATIC 
    ${LIB_Log_SRC}
    ${LIB_Utils_SRC}
    ${LIB_Cutils_SRC}
    ${LIB_Bionic_SRC}
)
