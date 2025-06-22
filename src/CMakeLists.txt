add_executable(Cabe
    Main.cpp
    Cabe.hpp

    Core/Event.hpp
    Core/Utils.hpp

    Core/Log.hpp
    Core/Log.cpp

    Core/File.hpp
    Core/FileManager.hpp
    Core/FileManager.cpp

    Core/IFrontend.hpp
    Core/IBackend.hpp

    Backends/BackendTemplate.hpp
    Frontends/FrontendTemplate.hpp
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

target_include_directories(Cabe PUBLIC
    ${CMAKE_SOURCE_DIR}/src/
)