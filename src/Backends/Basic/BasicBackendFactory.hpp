#pragma once

#include "BasicBackend.hpp"
#include "IBackendFactory.hpp"

class BasicBackendFactory : public Cabe::IBackendFactory
{
  public:
    ~BasicBackendFactory() override = default;

    std::unique_ptr<IBackend> create() const override
    {
        return std::make_unique<BasicBackend>();
    }
};
