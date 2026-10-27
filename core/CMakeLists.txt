add_library(winnetbyapp_core STATIC
    src/usage.cpp
)
add_library(winnetbyapp::core ALIAS winnetbyapp_core)

target_include_directories(winnetbyapp_core PUBLIC include)
target_link_libraries(winnetbyapp_core PRIVATE winnetbyapp_options)
