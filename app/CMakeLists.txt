add_executable(winnetbyapp
    main.cpp
)
target_compile_definitions(winnetbyapp PRIVATE UNICODE _UNICODE)
target_link_libraries(winnetbyapp PRIVATE
    winnetbyapp::core
    winnetbyapp_options
)
