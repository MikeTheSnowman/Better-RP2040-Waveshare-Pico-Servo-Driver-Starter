cmake_minimum_required(VERSION 3.12)

# Import Pico SDK
include(pico_sdk_import.cmake)

# Project name and languages
project(Pico_Servo_Driver C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

# Add subdirectories for libraries and examples
add_subdirectory(lib/Pico_Servo_Driver)
add_subdirectory(examples)

# Include directories for the main executable
include_directories(examples)
include_directories(lib/Pico_Servo_Driver)

# Create main executable
add_executable(main 
    main.c
)

# Enable USB output for printf, also enable UART output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(main)

# Link libraries
target_link_libraries(main 
    pico_stdlib 
    Pico_Servo_Driver
    examples
)
