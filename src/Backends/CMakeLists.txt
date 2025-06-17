if (USE_BACKEND_BASIC)
    add_subdirectory(Basic)
elseif (USE_BACKEND_GAPBUFFER)
    add_subdirectory(GapBuffer)
endif ()

target_include_directories(Backend PUBLIC
    ${CMAKE_SOURCE_DIR}/src/
)