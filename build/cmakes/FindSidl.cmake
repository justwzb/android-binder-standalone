set(Sidl_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/tools/sidl/)

file(GLOB_RECURSE Sidl_INCLUDE_FILES 
    ${PROJECT_SOURCE_DIR}/tools/sidl/*.cpp 
    ${PROJECT_SOURCE_DIR}/tools/sidl/*.h
    ${PROJECT_SOURCE_DIR}/tools/sidl/*.py
)

MESSAGE(STATUS "Sidl_INCLUDE_FILES: ${Sidl_INCLUDE_FILES}") 

IF (Sidl_INCLUDE_DIR)
    SET(Sidl_FOUND TRUE)
ENDIF (Sidl_INCLUDE_DIR)

IF (Sidl_FOUND)
    IF (NOT Sidl_FIND_QUIETLY)
        MESSAGE(STATUS "Found Sidl: ${Sidl_INCLUDE_DIR}") 
    ENDIF (NOT Sidl_FIND_QUIETLY)
ELSE (Sidl_FOUND)
    IF (Sidl_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find Sidl")
    ENDIF (Sidl_FIND_REQUIRED)
ENDIF (Sidl_FOUND)
