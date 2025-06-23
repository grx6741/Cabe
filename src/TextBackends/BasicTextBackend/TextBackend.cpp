#include "TextBackend.hpp"

void
BasicTextBackend::Populate(const std::string& content)
{
    m_Content = std::move(content);
}

std::string
BasicTextBackend::Dump()
{
    return m_Content;
}