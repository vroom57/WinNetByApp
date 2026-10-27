cmake_minimum_required(VERSION 3.25)

project(WinNetByApp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Static C++ runtime (/MT, /MTd) so users don't need the Visual C++
# Redistributable and the app ships as a single .exe.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

option(WINNETBYAPP_BUILD_TESTS "Build the unit tests" ON)

# Warning and conformance flags for WinNetByApp's own targets (not
# third-party code). Link it PRIVATE.
add_library(winnetbyapp_options INTERFACE)
if(MSVC)
    target_compile_options(winnetbyapp_options INTERFACE
        /W4 /WX /permissive- /utf-8 /Zc:__cplusplus)
else()
    target_compile_options(winnetbyapp_options INTERFACE
        -Wall -Wextra -Wpedantic -Werror)
endif()

add_subdirectory(core)

if(WIN32)
    add_subdirectory(app)
endif()

if(WINNETBYAPP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
