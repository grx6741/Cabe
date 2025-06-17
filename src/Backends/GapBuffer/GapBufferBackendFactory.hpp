#pragma once

#include "../../Common/IBackendFactory.hpp"
#include "GapBufferBackend.hpp"


class GapBufferBackendFactory : public Cabe::IBackendFactory
{
  public:
    ~GapBufferBackendFactory() override = default;

    std::unique_ptr<IBackend> create() const override
    {
        return std::make_unique<GapBufferBackend>();
    }
};