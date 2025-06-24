#include "Core/EventManager.hpp"

#include "Core/Utils.hpp"

#include "Core/Events/KeyEvent.hpp"
#include "Core/Events/OpenFileEvent.hpp"
#include "Core/Events/QuitEvent.hpp"
#include "Core/Events/TextInputEvent.hpp"

#include "Core/FileManager.hpp"

namespace Cabe {

void
EventManager::Handle(const KeyPressEvent& event)
{
    CABE_LOG_INFO("KeyPressEvent: key=%d mod=%d", event.GetKey(), event.GetMod());
}

void
EventManager::Handle(const KeyReleaseEvent& event)
{
    CABE_LOG_INFO("KeyReleaseEvent: key=%d mod=%d", event.GetKey(), event.GetMod());
}

void
EventManager::Handle(const OpenFileEvent& event)
{
    CABE_LOG_INFO("OpenFileEvent: files=%d", event.GetFiles().size());
    auto files = event.GetFiles();
    m_FileManager.OpenFiles(files);
}

void
EventManager::Handle(const TextInputEvent& event)
{
    CABE_LOG_INFO("TextInputEvent: text=%s", event.GetText().c_str());
}

void
EventManager::Handle(const QuitEvent& event)
{
    CABE_LOG_INFO("QuitEvent");
}

} // namespace Cabe