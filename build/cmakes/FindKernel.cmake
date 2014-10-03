#include kernel headers
IF($ENV{CMAKE_TARGET_ARCH} STREQUAL "arm")
    set(KERNEL_INCLUDE_DIR_ARCH
        ${PROJECT_SOURCE_DIR}/libs/include/kernel/arch-arm
    )
ELSEIF($ENV{CMAKE_TARGET_ARCH} STREQUAL "mips")
    set(KERNEL_INCLUDE_DIR_ARCH
        ${PROJECT_SOURCE_DIR}/libs/include/kernel/arch-mips
    )
ELSEIF($ENV{CMAKE_TARGET_ARCH} STREQUAL "x86")
    set(KERNEL_INCLUDE_DIR_ARCH
        ${PROJECT_SOURCE_DIR}/libs/include/kernel/arch-x86
    )
ELSE()
    MESSAGE(FATAL_ERROR "Unknown arch $ENV{CMAKE_TARGET_ARCH}")
ENDIF()

set(Kernel_INCLUDE_DIR
    ${KERNEL_INCLUDE_DIR_ARCH}
    ${PROJECT_SOURCE_DIR}/libs/include/kernel/common
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
