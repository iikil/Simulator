file(GLOB TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)


add_executable(TestMain 
    ${TEST_SOURCES}
    ${IMGUI_SOURCES}
    ${CMAKE_SOURCE_DIR}/OpenGL/src/glad.c
)

target_link_libraries(TestMain PRIVATE 
    glfw
    opengl32
    RenderCore
)

target_include_directories(TestMain PRIVATE 
    ${CMAKE_SOURCE_DIR}/Vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/Vendor/glad
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_SOURCE_DIR}/OpenGL/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS TestMain
    RUNTIME DESTINATION bin
)