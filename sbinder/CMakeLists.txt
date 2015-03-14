FIND_PACKAGE(AndroidToolsets REQUIRED)
INCLUDE_DIRECTORIES(${AndroidToolsets_INCLUDE_DIR})

FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

#binder
SET(LIB_Binder_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/binder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/BpBinder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/IPCThreadState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/IServiceManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/Parcel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/ProcessState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/IInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/Static.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/TextOutput.cpp #ProcessState.cpp used it alot
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/BufferedTextOutput.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binder/Debug.cpp
)

#sbinder, code added in this project
SET(LIB_SBINDER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/sbinder/RemoteCallbackList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sbinder/ICallbackList.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sbinder/sbinderServ.cpp
)


ADD_LIBRARY(StandaloneBinder SHARED 
    ${LIB_Binder_SRC}
    ${LIB_SBINDER_SRC}
)
TARGET_LINK_LIBRARIES(StandaloneBinder ${CMAKE_BINDER_LINKLIBS})
ADD_DEPENDENCIES(StandaloneBinder AndroidToolsets)
TARGET_LINK_LIBRARIES(StandaloneBinder AndroidToolsets)
