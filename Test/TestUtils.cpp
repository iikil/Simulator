#include "TestUtils.h"
#include <string>
#if defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif

namespace LivTest{

std::filesystem::path getExecutableDir() {
    std::filesystem::path exePath;

#if defined(_WIN32)
    wchar_t buffer[MAX_PATH];
    DWORD length = GetModuleFileNameW(NULL, buffer, MAX_PATH);
    if (length == 0 || length == MAX_PATH)
        throw std::runtime_error("Failed to get executable path on Windows.");
    exePath = std::filesystem::path(buffer).parent_path();

#elif defined(__APPLE__)
    char buffer[1024];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) != 0)
        throw std::runtime_error("Buffer too small for executable path on macOS.");
    exePath = std::filesystem::canonical(buffer).parent_path();

#elif defined(__linux__)
    char buffer[1024];
    ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (length == -1)
        throw std::runtime_error("Failed to get executable path on Linux.");
    buffer[length] = '\0';
    exePath = std::filesystem::canonical(buffer).parent_path();
#endif

    return exePath;
}

}      // LivTest