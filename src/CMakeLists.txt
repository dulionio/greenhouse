add_executable(${PROJECT_NAME}
  main.c
)

target_link_libraries(${PROJECT_NAME} ${LIBRARY})

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})
