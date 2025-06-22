#pragma once

#include <filesystem>
#include <string>
#include <variant>
#include <vector>


namespace Cabe {

enum class EEventType
{
    TextInput,
    KeyUp,
    KeyDown,
    OpenFile,
    SaveFile,
    Quit,
    None
};

enum class EKey
{
    CursorLeft,
    CursorRight,
    CursorUp,
    CursorDown,
    None
};

enum class EKeyMod
{
    CTRL = 0,
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
    std::variant<std::monostate,
                 std::string,
                 std::vector<std::filesystem::path>,
                 KeyboardInput>
      data;

    EventPayload()
      : type{ EEventType::None }
    {
    }
    ~EventPayload() {};
};

} // namespace Cabe
