cmake_minimum_required(VERSION 3.18.1)
project(nativeproc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_library(native-lib SHARED native-lib.cpp)

find_library(log-lib log)
find_library(android-lib android)
find_library(jnigraphics-lib jnigraphics)

if(DEFINED ENV{OpenCV_DIR})
    message(STATUS "Using OpenCV from $ENV{OpenCV_DIR}")
    set(OpenCV_DIR $ENV{OpenCV_DIR})
    find_package(OpenCV REQUIRED)
    target_compile_definitions(native-lib PRIVATE USE_OPENCV=1)
    target_include_directories(native-lib PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(native-lib ${OpenCV_LIBS})
else()
    message(WARNING "OpenCV_DIR not set. Building without OpenCV; will fallback to grayscale.")
endif()

target_link_libraries(native-lib ${log-lib} ${android-lib} ${jnigraphics-lib})
