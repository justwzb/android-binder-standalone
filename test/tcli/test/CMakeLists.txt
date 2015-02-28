INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include/)

set(TCLI_SIGNAL_TEST_SRC
   ${CMAKE_CURRENT_SOURCE_DIR}/test_main.c
)

ADD_EXECUTABLE(tcli_signal ${TCLI_SIGNAL_TEST_SRC})
ADD_DEPENDENCIES(tcli_signal tcli)
ADD_DEPENDENCIES(tcli_signal AndroidToolsets)
TARGET_LINK_LIBRARIES(tcli_signal tcli AndroidToolsets ${CMAKE_TEST_LINKLIBS})

#------------------------------
FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

FIND_PACKAGE(ServiceManager REQUIRED)
INCLUDE_DIRECTORIES(${ServiceManager_INCLUDE_DIR})

set(TCLI_TEST_SRC
   ${CMAKE_CURRENT_SOURCE_DIR}/test_tcli.c
)

ADD_EXECUTABLE(tcliServer ${TCLI_TEST_SRC})
set_target_properties(tcliServer PROPERTIES COMPILE_DEFINITIONS "BINDER_SERVICE")
ADD_DEPENDENCIES(tcliServer tcli)
ADD_DEPENDENCIES(tcliServer tcliproxyServer)
ADD_DEPENDENCIES(tcliServer AndroidToolsets)
ADD_DEPENDENCIES(tcliServer StandaloneBinder)
ADD_DEPENDENCIES(tcliServer libservicemanager)
TARGET_LINK_LIBRARIES(tcliServer tcli tcliproxyServer AndroidToolsets StandaloneBinder libservicemanager ${CMAKE_TEST_LINKLIBS})


ADD_EXECUTABLE(tcliClient ${TCLI_TEST_SRC})
set_target_properties(tcliClient PROPERTIES OUTPUT_NAME "tcli")
set_target_properties(tcliClient PROPERTIES COMPILE_DEFINITIONS "BINDER_CLIENT")
ADD_DEPENDENCIES(tcliClient AndroidToolsets)
ADD_DEPENDENCIES(tcliClient StandaloneBinder)
ADD_DEPENDENCIES(tcliClient tcliproxyClient)
TARGET_LINK_LIBRARIES(tcliClient AndroidToolsets StandaloneBinder tcliproxyClient ${CMAKE_TEST_LINKLIBS})
