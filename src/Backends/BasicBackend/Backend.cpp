#include "Backend.hpp"

#include "Utils.hpp"

std::unique_ptr<IBackend>
createBackend()
{
    return std::make_unique<BasicBackend>();
}

void
BasicBackend::Populate(const std::string& content)
{
    m_Content = std::move(content);
}

void
BasicBackend::ProcessEvent(const Cabe::EventPayload event)
{
    CABE_LOG_INFO("Processing event: %d", static_cast<int>(event.type));
    switch (event.type) {
        case Cabe::EEventType::TEXT_INPUT:
            break;
        case Cabe::EEventType::KEY_UP:
            break;
        case Cabe::EEventType::KEY_DOWN:
            break;
        case Cabe::EEventType::OPEN_FILE:
            break;
        case Cabe::EEventType::SAVE_FILE:
            break;
        case Cabe::EEventType::QUIT:
            break;
        case Cabe::EEventType::NONE:
            break;
    }
}

std::string
BasicBackend::Dump()
{
    return m_Content;
}
