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

    void Dispatch() override;
};

} // namespace Cabe