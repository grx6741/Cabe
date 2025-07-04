set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_DISABLE_INSTALL ON CACHE BOOL "" FORCE)

set(SDL_JOYSTICK		OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK_HIDAPI		OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK_RAWINPUT	OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK_WGI		OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK_XINPUT		OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK_DINPUT		OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC			OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI			OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI_JOYSTICK		OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI_LIBUSB		OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI_LIBUSB_SHARED	OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR			OFF CACHE BOOL "" FORCE)
set(SDL_CAMERA			OFF CACHE BOOL "" FORCE)
set(SDL_DUMMYCAMERA		OFF CACHE BOOL "" FORCE)
set(SDL_POWER			OFF CACHE BOOL "" FORCE)
set(SDL_OPENVR			OFF CACHE BOOL "" FORCE)
set(SDL_VIRTUAL_JOYSTICK	OFF CACHE BOOL "" FORCE)
set(SDL_TEST			OFF CACHE BOOL "" FORCE)
set(SDL_TESTS			OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY		OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES		OFF CACHE BOOL "" FORCE)
set(SDL_AUDIO			OFF CACHE BOOL "" FORCE)
set(SDL_DISKAUDIO		OFF CACHE BOOL "" FORCE)
set(SDL_DUMMYAUDIO		OFF CACHE BOOL "" FORCE)
set(SDL_PULSEAUDIO		OFF CACHE BOOL "" FORCE)
set(SDL_ALSA			OFF CACHE BOOL "" FORCE)
set(SDL_WASAPI			OFF CACHE BOOL "" FORCE)
set(SDL_SNDIO			OFF CACHE BOOL "" FORCE)
set(SDL_PIPEWIRE		OFF CACHE BOOL "" FORCE)
set(SDL_JACK			OFF CACHE BOOL "" FORCE)

add_subdirectory(${SDL_SRC_DIR} 
                 ${CMAKE_BINARY_DIR}/_deps/SDL-build 
                 EXCLUDE_FROM_ALL)

# imgui

add_library(imgui STATIC
    ${IMGUI_SRC_DIR}/imgui.cpp
    ${IMGUI_SRC_DIR}/imgui_demo.cpp
    ${IMGUI_SRC_DIR}/imgui_draw.cpp
    ${IMGUI_SRC_DIR}/imgui_tables.cpp
    ${IMGUI_SRC_DIR}/imgui_widgets.cpp
    ${IMGUI_SRC_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_SRC_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_SRC_DIR}
    ${IMGUI_SRC_DIR}/backends
)

target_link_libraries(imgui PUBLIC SDL3::SDL3)

add_library(RenderBackend STATIC
    RenderBackend.cpp
    RenderBackend.hpp
)

target_link_libraries(RenderBackend
    PUBLIC

    SDL3::SDL3
    imgui
)

target_include_directories(RenderBackend PUBLIC .)