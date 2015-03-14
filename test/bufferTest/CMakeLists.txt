FIND_PACKAGE(AndroidToolsets REQUIRED)
INCLUDE_DIRECTORIES(${AndroidToolsets_INCLUDE_DIR})

FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

FIND_PACKAGE(ServiceManager REQUIRED)
INCLUDE_DIRECTORIES(${ServiceManager_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

#SERVER for bufferTest
set(SAMPLE_BUFFERTEST_SRC_SERVICE
   ${CMAKE_CURRENT_SOURCE_DIR}/matrix_ringbuf.c
   ${CMAKE_CURRENT_SOURCE_DIR}/remote_buffer_module.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/remote_test_main.c
)

ADD_EXECUTABLE(bufferTestService ${SAMPLE_BUFFERTEST_SRC_SERVICE})
set_target_properties(bufferTestService PROPERTIES COMPILE_DEFINITIONS "BINDER_SERVICE")
ADD_DEPENDENCIES(bufferTestService StandaloneBinder)
ADD_DEPENDENCIES(libservicemanager StandaloneBinder)
TARGET_LINK_LIBRARIES(bufferTestService StandaloneBinder libservicemanager ${CMAKE_TEST_LINKLIBS})

#CLIENT for bufferTest
set(SAMPLE_BUFFERTEST_SRC_CLIENT
   ${CMAKE_CURRENT_SOURCE_DIR}/remote_buffer_module.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/remote_test_main.c
)

ADD_EXECUTABLE(bufferTestClient ${SAMPLE_BUFFERTEST_SRC_CLIENT})
set_target_properties(bufferTestClient PROPERTIES COMPILE_DEFINITIONS "BINDER_CLIENT")
ADD_DEPENDENCIES(bufferTestClient StandaloneBinder)
TARGET_LINK_LIBRARIES(bufferTestClient StandaloneBinder ${CMAKE_TEST_LINKLIBS})
