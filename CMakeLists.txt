cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_flash_memory)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico_flash_memory
              main.c)

# pull in common dependencies
target_link_libraries(pico_flash_memory 
                      pico_stdlib
                      hardware_gpio 
                      hardware_i2c 
                      hardware_uart 
                      hardware_adc 
                      hardware_flash 
                      hardware_dma 
                      hardware_spi 
                      hardware_irq
                      hardware_watchdog 
                      hardware_rtc )

# Enable usb output, disable uart output
pico_enable_stdio_usb(pico_flash_memory 1)
pico_enable_stdio_uart(pico_flash_memory 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_flash_memory)

