#include "Core/Events/KeyEvent.hpp"

#include "Core/EventManager.hpp"

namespace Cabe {

void
KeyPressEvent::Dispatch()
{
    EventManager::Get().Handle(*this);
}

void
KeyReleaseEvent::Dispatch()
{
    EventManager::Get().Handle(*this);
}

} // namespace Cabe