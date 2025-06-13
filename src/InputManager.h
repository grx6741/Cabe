#pragma once

#include <SDL3/SDL_events.h>

#include "Event.h"

namespace Cabe {

class InputManager {
   public:
    InputManager();
    ~InputManager();
    void GetEvent(EventPayload &event);

   private:
    void handleQuitEvent(SDL_Event &sdl_event, EventPayload &event);
    void handleKeyboardEvent(SDL_Event &sdl_event, EventPayload &event);
    void handleMouseEvent(SDL_Event &sdl_event, EventPayload &event);

    Cabe::KeyDirection getDirectionFromKey(const SDL_Keycode &key_code);
    Cabe::KeyMod getModFromKey(const SDL_Keymod &key_mod);
};

}  // namespace Cabe