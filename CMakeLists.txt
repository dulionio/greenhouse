cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(PICO_SDK_FETCH_FROM_GIT on)
set(PICO_BOARD pico_w)
set(LIBRARY pico_stdlib hardware_spi bme280)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/bme280.cmake)

project(greenhouse C CXX ASM)

pico_sdk_init()

add_subdirectory(src)
