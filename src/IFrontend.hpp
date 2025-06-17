#pragma once

#include "Event.hpp"

#include <vector>

class IFrontEnd
{
  public:
    virtual ~IFrontEnd() = default;

    virtual void PollEvent(Cabe::EventPayload& event) = 0;
    virtual bool IsRunning() = 0;
    virtual void RenderContent(const std::vector<std::string>& content) = 0;
};
