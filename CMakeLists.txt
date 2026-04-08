cmake_minimum_required(VERSION 3.16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(ssd1306_driver C ASM)
set(CMAKE_C_STANDARD 11)

add_executable(ssd1306_driver
    main.c
    bsp/i2c.c
    startup_stm32f103xb.s
    system_stm32f1xx.c
)

target_include_directories(ssd1306_driver PRIVATE
    bsp
    include
)

target_compile_options(ssd1306_driver PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -O0
    -g
    -specs=nosys.specs
    -DSTM32F103xB
)

target_link_options(ssd1306_driver PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -nostdlib
    -specs=nosys.specs
    -specs=nano.specs
    -T${CMAKE_SOURCE_DIR}/STM32F103XBTx_FLASH.ld
    -Wl,--gc-sections
)