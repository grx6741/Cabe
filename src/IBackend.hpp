#pragma once

#include "Event.hpp"


class IBackend
{
  public:
    virtual ~IBackend() = default;

    virtual void Populate(const std::string& content) = 0;
    virtual void ProcessEvent(const Cabe::EventPayload event) = 0;

    virtual std::string Dump() = 0;
};
