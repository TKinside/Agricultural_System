cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_PROJECT_NAME Agricultural_System)

# 包含工具链配置文件，它会设置好编译器和基础标志
include("cmake/gcc-arm-none-eabi.cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})

enable_language(C ASM)

message("Build type: " ${CMAKE_BUILD_TYPE})

add_executable(${CMAKE_PROJECT_NAME})
#target_link_options(${PROJECT_NAME} PRIVATE -u _printf_float)
# 自动收集源文件
file(GLOB_RECURSE USER_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/Driver/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/MiddleFile/*.c"
)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${USER_SOURCES})

# 添加头文件目录
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc"
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/Driver"
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/MiddleFile"
)

# 添加CubeMX生成的代码子目录
add_subdirectory(cmake/stm32cubemx)

# 将我们的可执行文件与CubeMX生成的库链接起来
target_link_libraries(${CMAKE_PROJECT_NAME}
        stm32cubemx
)

