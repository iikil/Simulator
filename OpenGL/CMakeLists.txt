cmake_minimum_required(VERSION 3.10)
project(Simulator)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 设置编译模式（默认Release）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 设置不同模式下的编译选项
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Ensure we're dynamically linking GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)  # <- Enable DLL build

add_subdirectory(vendor/glfw)

# Copy glfw3.dll after build (for Windows)
function(copy_glfw_dll target)
    if(WIN32)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE_DIR:glfw>/glfw3.dll"
                "$<TARGET_FILE_DIR:${target}>"
        )
    endif()
endfunction()

add_subdirectory(src)