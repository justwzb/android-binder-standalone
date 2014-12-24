FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

#binder
AUX_SOURCE_DIRECTORY(./binder LIB_Binder_SRC)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/SystemClock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Threads.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/misc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/SharedBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Static.cpp
    #on android, below files are only added on device.
    #${CMAKE_CURRENT_SOURCE_DIR}/libutils/Trace.cpp
)

#libcutils
SET(LIB_Cutils_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/atomic.c   #atomic.c.arm?
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/process_name.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/sched_policy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/threads.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/native_handle.c

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
    ${CMAKE_CURRENT_SOURCE_DIR}/bionic/libc/string/strlcpy.c
)

#sbinder, code added in this project
SET(LIB_SBINDER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/sbinder/RemoteCallbackList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sbinder/sbinderServ.cpp
)


ADD_LIBRARY(StandaloneBinder SHARED 
    ${LIB_Binder_SRC}
    ${LIB_Log_SRC}
    ${LIB_Utils_SRC}
    ${LIB_Cutils_SRC}
#    ${LIB_Bionic_SRC}
    ${LIB_SBINDER_SRC}
)
TARGET_LINK_LIBRARIES(StandaloneBinder $ENV{CMAKE_BINDER_LINKLIBS})
