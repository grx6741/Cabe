add_executable(Cabe
    Main.cpp

    Event.hpp
    Utils.hpp

    Log.hpp
    Log.cpp

    FileManager.hpp
    FileManager.cpp

    IFrontend.hpp
    IBackend.hpp
)

target_compile_definitions(Cabe PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

add_subdirectory(Backends)
add_subdirectory(Frontends)

target_link_libraries(Cabe
    PRIVATE
    Backend
    Frontend

    tomlplusplus::tomlplusplus
)