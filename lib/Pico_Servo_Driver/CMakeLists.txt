# Pico Servo Driver Library
# Find all source files in current directory
aux_source_directory(. DIR_Pico_Servo_Driver_SRCS)

# Create the servo driver library
add_library(Pico_Servo_Driver ${DIR_Pico_Servo_Driver_SRCS})

# Link against Pico SDK libraries
target_link_libraries(Pico_Servo_Driver PUBLIC 
    pico_stdlib 
    hardware_pwm
)
