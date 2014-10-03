FIND_PACKAGE(Kernel REQUIRED)
INCLUDE_DIRECTORIES(${Kernel_INCLUDE_DIR})

FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

#binder
AUX_SOURCE_DIRECTORY(./binder LIB_Binder_SRC)

#liblog
SET(LIB_Log_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/liblog/logd_write.c
    ${CMAKE_CURRENT_SOURCE_DIR}/liblog/logprint.c
    ${CMAKE_CURRENT_SOURCE_DIR}/liblog/event_tag_map.c
    ${CMAKE_CURRENT_SOURCE_DIR}/liblog/fake_log_device.c
)
ADD_DEFINITIONS(-DFAKE_LOG_DEVICE=1)

#libutils
SET(LIB_Utils_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/BasicHashtable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/BlobCache.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/CallStack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/FileMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/JenkinsHash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/LinearAllocator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/LinearTransform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Printer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/ProcessCallStack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/PropertyMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/RefBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/SharedBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Static.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/StopWatch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/String8.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/String16.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/SystemClock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Threads.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Timers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Tokenizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Unicode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/VectorImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/misc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libutils/Looper.cpp

    #on android, below files are only added on device.
    #${CMAKE_CURRENT_SOURCE_DIR}/libutils/Trace.cpp
)

#libcutils
SET(LIB_Cutils_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/hashmap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/atomic.c   #atomic.c.arm?
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/native_handle.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/socket_inaddr_any_server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/socket_local_client.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/socket_local_server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/socket_loopback_client.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/socket_loopback_server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/socket_network_client.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/sockets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/config_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/cpu_info.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/load_file.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/open_memstream.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/strdup16to8.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/strdup8to16.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/record_stream.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/process_name.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/threads.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/sched_policy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/iosched_policy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/str_parms.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/fs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/multiuser.c

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
    ${CMAKE_CURRENT_SOURCE_DIR}/libcutils/arch-arm/memset32.S
)

#bionic, only very limited needed c files are added
SET(LIB_Bionic_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/bionic/libc/string/strlcpy.c
)

ADD_LIBRARY(StandaloneBinder SHARED 
    ${LIB_Binder_SRC}
    ${LIB_Log_SRC}
    ${LIB_Utils_SRC}
    ${LIB_Cutils_SRC}
    ${LIB_Bionic_SRC}
)
TARGET_LINK_LIBRARIES(StandaloneBinder pthread)
