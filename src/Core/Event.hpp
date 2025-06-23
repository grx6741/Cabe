#pragma once

namespace Cabe {

enum class EEventType
{
    TextInput,
    KeyPress,
    KeyRelease,
    OpenFile,
    SaveFile,
    Quit,
    None
};

class IEvent
{
  public:
    const EEventType GetType() const { return m_Type; }
    virtual void Dispatch() = 0;

    virtual ~IEvent() = default;

  protected:
    IEvent(const EEventType type)
      : m_Type{ type }
    {
    }
    EEventType m_Type;
};

} // namespace Cabe
