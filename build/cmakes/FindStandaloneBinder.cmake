#FIND_PATH(StandaloneBinder_INCLUDE_DIR binder/binder.h ${PROJECT_SOURCE_DIR}/libs/include/)
set(StandaloneBinder_INCLUDE_DIR 
    ${PROJECT_SOURCE_DIR}/sbinder/include/ #head files of libs
    )

IF (StandaloneBinder_INCLUDE_DIR)
    SET(StandaloneBinder_FOUND TRUE)
ENDIF (StandaloneBinder_INCLUDE_DIR)

IF (StandaloneBinder_FOUND)
    IF (NOT StandaloneBinder_FIND_QUIETLY)
        MESSAGE(STATUS "Found StandaloneBinder: ${StandaloneBinder_INCLUDE_DIR}") 
    ENDIF (NOT StandaloneBinder_FIND_QUIETLY)
ELSE (StandaloneBinder_FOUND)
    IF (StandaloneBinder_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find StandaloneBinder")
    ENDIF (StandaloneBinder_FIND_REQUIRED)
ENDIF (StandaloneBinder_FOUND)
