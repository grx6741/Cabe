add_subdirectory(SDL3BuiltIn)

target_include_directories(RenderBackend PUBLIC
    ${CMAKE_SOURCE_DIR}/src/
)