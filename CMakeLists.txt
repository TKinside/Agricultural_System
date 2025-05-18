cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_PROJECT_NAME Agricultural_System)

include("cmake/gcc-arm-none-eabi.cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
enable_language(C ASM)

project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

add_executable(${CMAKE_PROJECT_NAME})

# 自动收集Core/Src里所有.c和.cpp文件
file(GLOB_RECURSE USER_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.cpp"
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${USER_SOURCES})

# 加入Core/Inc为头文件目录
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc"
)

# CubeMX自动生成代码由子目录管理
add_subdirectory(cmake/stm32cubemx)

target_link_libraries(${CMAKE_PROJECT_NAME}
        stm32cubemx
)
