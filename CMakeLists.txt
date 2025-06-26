cmake_minimum_required(VERSION 3.10)
project(PhysGL)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build Test" OFF)  # 默认关闭

# 设置编译模式（默认Release）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 设置不同模式下的编译选项
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# 设置安装目录
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/Output" CACHE PATH "Install path")

# ————————————————————————————————————————————————————————————————————————

add_subdirectory(OpenGL)

add_subdirectory(Vendor)

if (BUILD_TESTS)
    message(STATUS "Build Test: ${BUILD_TESTS}")
    add_subdirectory(Test)
endif()

add_executable(PhysGL 
    main.cpp
    OpenGL/src/glad.c
)

target_link_libraries(PhysGL PRIVATE 
    glfw
    opengl32
)

target_include_directories(PhysGL PRIVATE 
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glad
)

install(TARGETS PhysGL
    RUNTIME DESTINATION bin
)