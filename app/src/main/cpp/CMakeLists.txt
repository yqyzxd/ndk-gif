
cmake_minimum_required(VERSION 3.4.1)

file(GLOB giflib_src ${CMAKE_SOURCE_DIR}/giflib/*.c)

include_directories(${CMAKE_SOURCE_DIR}/giflib)

add_library( # Sets the name of the library.
        gif-lib

        SHARED

        log.h
        ${giflib_src}
        GifFrame.cpp
        JavaInputSream.cpp
        ../jni/com_wind_ndk_gif_GifFrame.cpp)

find_library(
        log-lib
        log)
find_library(
        android-lib
        android)

find_library(
        jnigraphics-lib
        jnigraphics)
target_link_libraries(
        gif-lib

        ${android-lib}
        ${jnigraphics-lib}
        ${log-lib})