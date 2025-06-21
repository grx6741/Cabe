#pragma once

#include <variant>
#include <string>
#include <vector>

namespace Cabe {

enum class EEventType
{
    TEXT_INPUT,
    KEY_UP,
    KEY_DOWN,
    OPEN_FILE,
    SAVE_FILE,
    QUIT,
    NONE
};

enum class EKey
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
    EKey direction;
    EKeyMod mod;
};

struct EventPayload
{
    EEventType type;
    std::variant<
	std::monostate, 
	std::string, 
	std::vector<std::string>,
	KeyboardInput
    > data;

    EventPayload()
      : type{EEventType::NONE}
    {
    }
    ~EventPayload() {};
};

} // namespace Cabe
