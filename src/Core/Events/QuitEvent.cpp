#include "Core/Events/QuitEvent.hpp"

#include "Core/EventManager.hpp"

namespace Cabe {

void
QuitEvent::Dispatch()
{
    EventManager::Get().Handle(*this);
}

} // namespace Cabe