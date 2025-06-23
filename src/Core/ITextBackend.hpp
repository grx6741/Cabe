#pragma once

#include <string>

namespace Cabe {

class ITextBackend
{
  public:
    virtual ~ITextBackend() = default;

    virtual void Populate(const std::string& content) = 0;
    virtual std::string Dump() = 0;
};

} // namespace Cabe