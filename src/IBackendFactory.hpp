#pragma once

#include "IBackend.hpp"

namespace Cabe {

class IBackendFactory
{
  public:
    virtual ~IBackendFactory() = default;

    virtual std::unique_ptr<IBackend> create() const = 0;
};

} // namespace Cabe
