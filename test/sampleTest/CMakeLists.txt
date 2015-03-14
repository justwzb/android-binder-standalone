FIND_PACKAGE(AndroidToolsets REQUIRED)
INCLUDE_DIRECTORIES(${AndroidToolsets_INCLUDE_DIR})

FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

FIND_PACKAGE(ServiceManager REQUIRED)
INCLUDE_DIRECTORIES(${ServiceManager_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

FIND_PACKAGE(Sidl REQUIRED)

#generate sample_module and remote code
SET(SAMPLETEST_MODULE_CODE_LIST
    ${CMAKE_CURRENT_BINARY_DIR}/sample_module.c
    ${CMAKE_CURRENT_BINARY_DIR}/sample_module.h
    ${CMAKE_CURRENT_BINARY_DIR}/remote_sample_module.sidl
    ${CMAKE_CURRENT_BINARY_DIR}/remote_sample_module.h
    ${CMAKE_CURRENT_BINARY_DIR}/remote_sample_module.cpp
)
ADD_CUSTOM_COMMAND(OUTPUT ${SAMPLETEST_MODULE_CODE_LIST} 
    COMMAND echo "Generating sample_module code file..."
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/genSampleApis.py
    COMMAND python ${PROJECT_SOURCE_DIR}/tools/sidl/sidl.py ${CMAKE_CURRENT_BINARY_DIR}/remote_sample_module.sidl
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/genSampleApis.py
    DEPENDS ${Sidl_INCLUDE_FILES}
    )

ADD_CUSTOM_TARGET(sampleTestCode DEPENDS ${SAMPLETEST_MODULE_CODE_LIST})

#Service for sampleTest
set(SAMPLETEST_SRC_SERVICE
   ${CMAKE_CURRENT_BINARY_DIR}/sample_module.c
   ${CMAKE_CURRENT_BINARY_DIR}/remote_sample_module.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/remote_test_main.c
)
ADD_EXECUTABLE(sampleTestService ${SAMPLETEST_SRC_SERVICE})
set_target_properties(sampleTestService PROPERTIES COMPILE_DEFINITIONS "BINDER_SERVICE")
ADD_DEPENDENCIES(sampleTestService StandaloneBinder)
ADD_DEPENDENCIES(libservicemanager StandaloneBinder)
TARGET_LINK_LIBRARIES(sampleTestService StandaloneBinder libservicemanager ${CMAKE_TEST_LINKLIBS})

#Client for sampleTest
set(SAMPLETEST_SRC_CLIENT
   ${CMAKE_CURRENT_BINARY_DIR}/remote_sample_module.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/remote_test_main.c
)
ADD_EXECUTABLE(sampleTestClient ${SAMPLETEST_SRC_CLIENT})
set_target_properties(sampleTestClient PROPERTIES COMPILE_DEFINITIONS "BINDER_CLIENT")
ADD_DEPENDENCIES(sampleTestClient StandaloneBinder)
TARGET_LINK_LIBRARIES(sampleTestClient StandaloneBinder ${CMAKE_TEST_LINKLIBS})
