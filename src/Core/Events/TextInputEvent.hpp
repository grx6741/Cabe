#pragma once

#include "Core/Event.hpp"

#include <string>

namespace Cabe {

class TextInputEvent : public IEvent
{
  public:
    inline TextInputEvent(const std::string& text)
      : m_Text{ text }
      , IEvent{ EEventType::TextInput }
    {
    }

    inline TextInputEvent()
      : TextInputEvent{ "" }
    {
    }

    ~TextInputEvent() override = default;

    inline const std::string& GetText() const { return m_Text; }
    inline void SetText(const std::string& text) { m_Text = text; }

    void Dispatch() override;

  private:
    std::string m_Text;
};

} // namespace Cabe