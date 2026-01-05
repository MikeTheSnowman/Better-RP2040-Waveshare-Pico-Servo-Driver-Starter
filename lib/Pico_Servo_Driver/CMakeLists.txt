# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_Config_SRCS 变量
aux_source_directory(. DIR_Pico_Servo_Driver_SRCS)

include_directories(../Config)

# 生成链接库
add_library(Pico_Servo_Driver ${DIR_Pico_Servo_Driver_SRCS})
target_link_libraries(Pico_Servo_Driver PUBLIC Config)