cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CONFIG_ROOT ${PROJECT_SOURCE_DIR}/build/configs/)
INCLUDE(${CMAKE_CONFIG_ROOT}/config_$ENV{CMAKE_PLATFORM_NAME}.txt)

#put output to out folder
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/$ENV{CMAKE_PLATFORM_NAME}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/$ENV{CMAKE_PLATFORM_NAME}/lib)

#set module search path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/build/cmakes/)

#add moduels to compile
if(EXISTS ${PROJECT_SOURCE_DIR}/androidtoolsets)
    ADD_SUBDIRECTORY(androidtoolsets)
endif(EXISTS ${PROJECT_SOURCE_DIR}/androidtoolsets)

if(EXISTS ${PROJECT_SOURCE_DIR}/sbinder)
    ADD_SUBDIRECTORY(sbinder)
endif(EXISTS ${PROJECT_SOURCE_DIR}/sbinder)

if(EXISTS ${PROJECT_SOURCE_DIR}/servicemanager)
    ADD_SUBDIRECTORY(servicemanager) 
endif(EXISTS ${PROJECT_SOURCE_DIR}/servicemanager)

if(EXISTS ${PROJECT_SOURCE_DIR}/test)
    ADD_SUBDIRECTORY(test) 
endif(EXISTS ${PROJECT_SOURCE_DIR}/test)


if(EXISTS ${PROJECT_SOURCE_DIR}/kmodule)
    #ADD_SUBDIRECTORY(kmodule) 
endif(EXISTS ${PROJECT_SOURCE_DIR}/kmodule)
