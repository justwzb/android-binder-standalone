FIND_PACKAGE(AndroidToolsets REQUIRED)
INCLUDE_DIRECTORIES(${AndroidToolsets_INCLUDE_DIR})

FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

FIND_PACKAGE(ServiceManager REQUIRED)
INCLUDE_DIRECTORIES(${ServiceManager_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include/)

AUX_SOURCE_DIRECTORY(. LIB_TCLI_PROXY_SRC)

ADD_LIBRARY(tcliproxyClient SHARED ${LIB_TCLI_PROXY_SRC})
set_target_properties(tcliproxyClient PROPERTIES COMPILE_DEFINITIONS "BINDER_CLIENT")
TARGET_LINK_LIBRARIES(tcliproxyClient ${CMAKE_BINDER_LINKLIBS} AndroidToolsets StandaloneBinder)
ADD_DEPENDENCIES(tcliproxyClient AndroidToolsets StandaloneBinder)

ADD_LIBRARY(tcliproxyServer SHARED ${LIB_TCLI_PROXY_SRC})
set_target_properties(tcliproxyServer PROPERTIES COMPILE_DEFINITIONS "BINDER_SERVICE")
TARGET_LINK_LIBRARIES(tcliproxyServer ${CMAKE_BINDER_LINKLIBS} AndroidToolsets StandaloneBinder)
ADD_DEPENDENCIES(tcliproxyServer AndroidToolsets StandaloneBinder)
