# Ensure we're dynamically linking GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL " " FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_LIBRARY_TYPE "SHARED" CACHE STRING " " FORCE)  # <- Enable DLL build

add_subdirectory(glfw)

install(
    FILES $<TARGET_FILE:glfw>
    DESTINATION bin
)

