add_subdirectory(BasicTextBackend)

target_include_directories(TextBackend PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)