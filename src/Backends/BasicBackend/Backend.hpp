#pragma once

#include "Backends/BackendTemplate.hpp"

class BasicBackend : public Cabe::IBackend
{
    CABE_BACKEND_TEMPLATE

  public:
    BasicBackend() = default;
    ~BasicBackend() override = default;

  private:
    std::string m_Content;
};

CABE_BACKEND_TEMPLATE_CREATOR(BasicBackend);