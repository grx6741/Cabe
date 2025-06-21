#pragma once

#include "Event.hpp"

class IBackend
{
  public:
    virtual ~IBackend() = default;

    virtual void Populate(const std::string& content) = 0;
    virtual std::string Dump() = 0;
};
