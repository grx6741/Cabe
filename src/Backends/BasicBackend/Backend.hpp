#pragma once

#include "BackendTemplate.hpp"

#include <memory>

class BasicBackend : public IBackend
{
    CABE_BACKEND_TEMPLATE

  public:
    BasicBackend() = default;
    ~BasicBackend() override = default;

  private:
    std::string m_Content;
};

CABE_BACKEND_TEMPLATE_CREATOR(BasicBackend);