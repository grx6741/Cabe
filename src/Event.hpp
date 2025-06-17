#pragma once

#include "Utils.hpp"

#include <variant>

namespace Cabe {

enum class EEventType
{
    TEXT_INPUT,
    KEY_UP,
    KEY_DOWN,
    QUIT
};

enum class EKeyDirection
{
    ARROW_LEFT,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    NONE
};

enum class EKeyMod
{
    CTRL,
    SHIFT,
    ALT,
    NONE
};

struct KeyboardInput
{
    EKeyDirection direction;
    EKeyMod mod;
};

struct EventPayload
{
    EEventType type;
    std::variant<std::monostate, std::string, KeyboardInput> data;

    EventPayload() {}
    ~EventPayload() {};
};

} // namespace Cabe
