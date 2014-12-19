#FIND_PATH(ServiceManager_INCLUDE_DIR binder/binder.h ${PROJECT_SOURCE_DIR}/libs/include/)
set(ServiceManager_INCLUDE_DIR 
    ${PROJECT_SOURCE_DIR}/servicemanager/include/ #head files of libs
    )

IF (ServiceManager_INCLUDE_DIR)
    SET(ServiceManager_FOUND TRUE)
ENDIF (ServiceManager_INCLUDE_DIR)

IF (ServiceManager_FOUND)
    IF (NOT ServiceManager_FIND_QUIETLY)
        MESSAGE(STATUS "Found ServiceManager: ${ServiceManager_INCLUDE_DIR}") 
    ENDIF (NOT ServiceManager_FIND_QUIETLY)
ELSE (ServiceManager_FOUND)
    IF (ServiceManager_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find ServiceManager")
    ENDIF (ServiceManager_FIND_REQUIRED)
ENDIF (ServiceManager_FOUND)
