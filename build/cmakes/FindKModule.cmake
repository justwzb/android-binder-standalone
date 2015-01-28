#include kernel module headers
set(KModule_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/kmodule
)

IF (Kmodule_INCLUDE_DIR)
    SET(Kmodule_FOUND TRUE)
ENDIF (Kmodule_INCLUDE_DIR)

IF (Kmodule_FOUND)
    IF (NOT Kmodule_FIND_QUIETLY)
        MESSAGE(STATUS "Found kmodule: ${Kmodule_INCLUDE_DIR}") 
    ENDIF (NOT Kmodule_FIND_QUIETLY)
ELSE (Kmodule_FOUND)
    IF (Kmodule_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find kmodule")
    ENDIF (Kmodule_FIND_REQUIRED)
ENDIF (Kmodule_FOUND)
