AUX_SOURCE_DIRECTORY(./src LIB_StandaloneBinder_SRC)

FIND_PACKAGE(StandaloneBinder REQUIRED)
INCLUDE_DIRECTORIES(${StandaloneBinder_INCLUDE_DIR})

ADD_LIBRARY(StandaloneBinder SHARED ${LIB_StandaloneBinder_SRC})