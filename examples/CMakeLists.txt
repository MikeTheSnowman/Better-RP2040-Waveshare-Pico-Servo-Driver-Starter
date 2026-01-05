# Example programs for Pico Servo Driver
# Find all source files in current directory
aux_source_directory(. DIR_examples_SRCS)

# Include the servo driver headers
include_directories(../lib/Pico_Servo_Driver)

# Create examples library
add_library(examples ${DIR_examples_SRCS})

# Link against servo driver library and math library
target_link_libraries(examples PUBLIC Pico_Servo_Driver m)
