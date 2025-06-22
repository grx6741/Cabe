#include "Backend.hpp"

void
BasicBackend::Populate(const std::string& content)
{
    m_Content = std::move(content);
}

std::string
BasicBackend::Dump()
{
    return m_Content;
}