#include "Core/Events/OpenFileEvent.hpp"

#include "Core/EventManager.hpp"

namespace Cabe {

void
OpenFileEvent::Dispatch()
{
    EventManager::Get().Handle(*this);
}

} // namespace Cabe