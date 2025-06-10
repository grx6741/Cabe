add_subdirectory(text)

add_executable(Cabe
    main.cpp
    File.cpp
)

target_compile_definitions(Cabe PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_link_libraries(Cabe
    PRIVATE
    text

    SDL3::SDL3
    imgui
    tomlplusplus::tomlplusplus
)