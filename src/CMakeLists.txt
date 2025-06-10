add_executable(Cabe
    main.cpp
)

target_compile_definitions(Cabe PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_link_libraries(Cabe
    PRIVATE
    SDL3::SDL3
    imgui
    tomlplusplus::tomlplusplus
)