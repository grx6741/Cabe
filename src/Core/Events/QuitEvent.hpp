#pragma once

#include "Core/Event.hpp"

namespace Cabe {

class QuitEvent : public IEvent
{
  public:
    inline QuitEvent()
      : IEvent{ EEventType::Quit }
    {
    }

    void Dispatch(EventManager& event_manager) const override
    {
        event_manager.Handle(*this);
    }
};

} // namespace Cabe