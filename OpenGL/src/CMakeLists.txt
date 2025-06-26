file(GLOB RENDERER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# 1. 定义一个库（STATIC 或 OBJECT）
add_library(RenderCore STATIC
    ${RENDERER_SOURCES}   
)

# 2. 添加 include 路径
target_include_directories(RenderCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Vendor/glad
    ${CMAKE_SOURCE_DIR}/Vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/Vendor/glm
    ${CMAKE_SOURCE_DIR}/Vendor/stb_image
)

# 3. 添加对 glad / glfw 的依赖
target_link_libraries(RenderCore PUBLIC
    glfw
    opengl32
)

install(TARGETS RenderCore
    ARCHIVE DESTINATION Render/lib
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION Render/include
    FILES_MATCHING PATTERN "*.h"
)