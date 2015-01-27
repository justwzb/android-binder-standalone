#include kernel headers
IF(CMAKE_TARGET_ARCH STREQUAL "arm")
    set(KERNEL_INCLUDE_DIR_ARCH
        ${PROJECT_SOURCE_DIR}/libs/bionic/libc/kernel/arch-arm
    )
ELSEIF(CMAKE_TARGET_ARCH STREQUAL "mips")
    set(KERNEL_INCLUDE_DIR_ARCH
        ${PROJECT_SOURCE_DIR}/libs/bionic/libc/kernel/arch-mips
    )
ELSEIF(CMAKE_TARGET_ARCH STREQUAL "x86")
    set(KERNEL_INCLUDE_DIR_ARCH
        ${PROJECT_SOURCE_DIR}/libs/bionic/libc/kernel/arch-x86
    )
ELSE()
    MESSAGE(FATAL_ERROR "Unknown arch $ENV{CMAKE_TARGET_ARCH}")
ENDIF()

set(Kernel_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/libs/bionic/libc/kernel/common
    ${KERNEL_INCLUDE_DIR_ARCH}
)

IF (Kernel_INCLUDE_DIR)
    SET(Kernel_FOUND TRUE)
ENDIF (Kernel_INCLUDE_DIR)

IF (Kernel_FOUND)
    IF (NOT Kernel_FIND_QUIETLY)
        MESSAGE(STATUS "Found Kernel: ${Kernel_INCLUDE_DIR}") 
    ENDIF (NOT Kernel_FIND_QUIETLY)
ELSE (Kernel_FOUND)
    IF (Kernel_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find Kernel")
    ENDIF (Kernel_FIND_REQUIRED)
ENDIF (Kernel_FOUND)
