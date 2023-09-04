add_definitions(-DBME280_32BIT_ENABLE)

add_library(bme280 INTERFACE)

target_sources(bme280 INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/lib/BME280_driver/bme280.c
)

target_include_directories(bme280 INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/lib/BME280_driver/
)

target_link_libraries(bme280 INTERFACE pico_stdlib)
