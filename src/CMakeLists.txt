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

    Core/EventManager.cpp
    Core/EventManager.hpp

    Core/IRenderBackend.hpp
    Core/ITextBackend.hpp

    Core/Events/KeyEvent.hpp
    Core/Events/KeyEvent.cpp
    Core/Events/OpenFileEvent.hpp
    Core/Events/OpenFileEvent.cpp
    Core/Events/QuitEvent.hpp
    Core/Events/QuitEvent.cpp
    Core/Events/TextInputEvent.hpp
    Core/Events/TextInputEvent.cpp

    TextBackends/TextBackendTemplate.hpp
    RenderBackends/RenderBackendTemplate.hpp
)

target_compile_definitions(Cabe PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

add_subdirectory(TextBackends)
add_subdirectory(RenderBackends)

target_link_libraries(Cabe
    PRIVATE
    TextBackend
    RenderBackend

    tomlplusplus::tomlplusplus
)

target_include_directories(Cabe PUBLIC
    ${CMAKE_SOURCE_DIR}/src/
)