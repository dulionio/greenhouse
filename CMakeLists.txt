cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(LIBRARY pico_stdlib)
set(PICO_SDK_FETCH_FROM_GIT on)
set(PICO_BOARD pico_w)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(greenhouse C CXX ASM)

pico_sdk_init()

add_subdirectory(src)
