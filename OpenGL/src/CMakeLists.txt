add_executable(Simulator 
    main.cpp
    glad.c
)

target_link_libraries(Simulator PRIVATE 
    glfw
    opengl32
)

target_include_directories(Simulator PRIVATE 
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glad
)

copy_glfw_dll(Simulator)