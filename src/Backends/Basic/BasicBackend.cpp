#include "BasicBackend.hpp"

void
BasicBackend::Populate(const std::string& content)
{
    m_Content = std::move(content);
}

void
BasicBackend::ProcessEvent(const Cabe::EventPayload event)
{
    // TODO: Process event
}

std::string
BasicBackend::Dump()
{
    return m_Content;
}
