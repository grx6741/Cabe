#include "InputManager.h"

namespace Cabe {

// Public

InputManager::InputManager() {}

InputManager::~InputManager() {}

void InputManager::GetEvent(EventPayload &event) {
    SDL_Event sdl_event;
    SDL_WaitEvent(&sdl_event);

    handleQuitEvent(sdl_event, event);

    handleKeyboardEvent(sdl_event, event);

    // handleMouseEvent(sdl_event, event);
}

// Private

void InputManager::handleQuitEvent(SDL_Event &sdl_event, EventPayload &event) {
    if (sdl_event.type == SDL_EVENT_QUIT) event.type = Event::QUIT;
}

void InputManager::handleKeyboardEvent(SDL_Event &sdl_event,
                                       EventPayload &event) {
    switch (sdl_event.type) {
        case SDL_EVENT_TEXT_INPUT: {
            event.type = Event::TEXT_INPUT;
            event.data = std::string(sdl_event.text.text);
            break;
        }

        case SDL_EVENT_KEY_DOWN: {
            event.type = Event::KEY_DOWN;
            event.data = KeyboardInput{ getDirectionFromKey(sdl_event.key.key),
                                        getModFromKey(sdl_event.key.mod) };
            break;
        }

        case SDL_EVENT_KEY_UP: {
            event.type = Event::KEY_UP;
            event.data = KeyboardInput{ getDirectionFromKey(sdl_event.key.key),
                                        getModFromKey(sdl_event.key.mod) };
            break;
        }

        default: break;
    }
}

void InputManager::handleMouseEvent(SDL_Event &sdl_event, EventPayload &event) {
    CABE_TODO;
}

Cabe::KeyDirection InputManager::getDirectionFromKey(const SDL_Keycode &key_code) {
    switch (key_code) {
        case SDLK_LEFT:     return KeyDirection::LEFT;
        case SDLK_RIGHT:    return KeyDirection::RIGHT;
        case SDLK_UP:       return KeyDirection::UP;
        case SDLK_DOWN:     return KeyDirection::DOWN;
    }

    return KeyDirection::NONE;
}

KeyMod InputManager::getModFromKey(const SDL_Keymod &key_mod) {
    if (key_mod & SDL_KMOD_CTRL)    return KeyMod::CTRL;
    if (key_mod & SDL_KMOD_SHIFT)   return KeyMod::SHIFT;
    if (key_mod & SDL_KMOD_ALT)     return KeyMod::ALT;

    return KeyMod::NONE;
}

}  // namespace Cabe