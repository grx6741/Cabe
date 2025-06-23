#pragma once

#include "TextBackends/TextBackendTemplate.hpp"

class BasicTextBackend : public Cabe::ITextBackend
{
    CABE_TEXT_BACKEND_TEMPLATE

  public:
    BasicTextBackend() = default;
    ~BasicTextBackend() override = default;

  private:
    std::string m_Content;
};

CABE_TEXT_BACKEND_TEMPLATE_CREATOR(BasicTextBackend);