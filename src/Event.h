#pragma once

#include "Utils.h"

namespace Cabe {

enum class Event { TEXT_INPUT, KEY_UP, KEY_DOWN, QUIT };
enum class KeyDirection { LEFT, RIGHT, UP, DOWN, NONE };
enum class KeyMod { CTRL, SHIFT, ALT, NONE };

struct KeyboardInput {
    KeyDirection direction;
    KeyMod mod;
};

struct EventPayload {
    Event type;
    std::variant<
        std::monostate,
        std::string,
        KeyboardInput
    > data;

    EventPayload() {}
    ~EventPayload() {};
};

}  // namespace Cabe