if (USE_FRONTEND_SDL3BUILTIN)
    add_subdirectory(SDL3BuiltIn)
endif()

target_include_directories(Frontend PUBLIC
    ${CMAKE_SOURCE_DIR}/src/
)