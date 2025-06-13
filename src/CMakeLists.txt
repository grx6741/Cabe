add_subdirectory(text)

add_executable(Cabe
    main.cpp

    File.h
    File.cpp
)

target_compile_definitions(Cabe PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_link_libraries(Cabe
    PRIVATE
    Text

    SDL3::SDL3
    imgui
    tomlplusplus::tomlplusplus
)