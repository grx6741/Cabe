#include "TextInputEvent.hpp"

#include "Core/EventManager.hpp"

namespace Cabe {

void
TextInputEvent::Dispatch()
{
    EventManager::Get().Handle(*this);
}

} // namespace Cabe