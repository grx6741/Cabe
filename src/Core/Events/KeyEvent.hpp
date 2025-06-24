#pragma once

#include "Core/Event.hpp"

namespace Cabe {

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

class KeyEvent : public IEvent
{
  public:
    inline KeyEvent(const EKey key,
                    const EKeyMod mod = EKeyMod::NONE,
                    const bool pressed = true)
      : m_Key{ key }
      , m_Mod{ mod }
      , IEvent{ pressed ? EEventType::KeyPress : EEventType::KeyRelease }
    {
    }

    ~KeyEvent() override = default;

    inline const EKey GetKey() const { return m_Key; }
    inline const EKeyMod GetMod() const { return m_Mod; }

    inline void SetKey(const EKey key) { m_Key = key; }
    inline void SetMod(const EKeyMod mod) { m_Mod = mod; }

  private:
    EKey m_Key;
    EKeyMod m_Mod;
};

class KeyPressEvent : public KeyEvent
{
  public:
    KeyPressEvent(const EKey key, const EKeyMod mod = EKeyMod::NONE)
      : KeyEvent(key, mod, true)
    {
    }

    inline void Dispatch(EventManager& event_manager) const override
    {
        event_manager.Handle(*this);
    }
};

class KeyReleaseEvent : public KeyEvent
{
  public:
    KeyReleaseEvent(const EKey key, const EKeyMod mod = EKeyMod::NONE)
      : KeyEvent(key, mod, false)
    {
    }

    inline void Dispatch(EventManager& event_manager) const override
    {
        event_manager.Handle(*this);
    }
};

}