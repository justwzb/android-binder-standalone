FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

set(SAMPLETEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sampleTest)

#Service for sampleTest
set(SAMPLETEST_SRC_SERVICE
   ${SAMPLETEST_SRC_DIR}/sample_module.c
   ${SAMPLETEST_SRC_DIR}/remote_sample_module.cpp
   ${SAMPLETEST_SRC_DIR}/remote_test_main.c
)
ADD_EXECUTABLE(sampleTestService ${SAMPLETEST_SRC_SERVICE})
set_target_properties(sampleTestService PROPERTIES COMPILE_DEFINITIONS "BINDER_SERVICE")
ADD_DEPENDENCIES(sampleTestService StandaloneBinder)
TARGET_LINK_LIBRARIES(sampleTestService StandaloneBinder)

#Client for sampleTest
set(SAMPLETEST_SRC_CLIENT
   ${SAMPLETEST_SRC_DIR}/remote_sample_module.cpp
   ${SAMPLETEST_SRC_DIR}/remote_test_main.c
)
ADD_EXECUTABLE(sampleTestClient ${SAMPLETEST_SRC_SERVICE})
set_target_properties(sampleTestClient PROPERTIES COMPILE_DEFINITIONS "BINDER_CLIENT")
ADD_DEPENDENCIES(sampleTestClient StandaloneBinder)