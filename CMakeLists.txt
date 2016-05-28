cmake_minimum_required(VERSION 3.3)
project(EAN)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64 ")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(SOURCE_FILES logicmain.cpp NumericalPeriodSpline.cpp NumericalPeriodSpline.h Exceptions.h Utilities.cpp Utilities.h DataReader.cpp DataReader.h IntervalPeriodSpline.cpp IntervalPeriodSpline.h logicmain.h)


set(Boost_INCLUDE_DIR /usr/local/boost)
set(Boost_LIBRARY_DIR /usr/local/boost/stage/lib)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})



add_executable(EAN ${SOURCE_FILES})



set(EXTRA_LIBS /usr/lib/x86_64-linux-gnu/libmpfr.a /usr/lib/x86_64-linux-gnu/libgmp.a)
target_link_libraries(EAN ${EXTRA_LIBS} ${Boost_LIBRARIES})