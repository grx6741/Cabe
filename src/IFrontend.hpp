#pragma once

#include "Event.hpp"
#include "FileManager.hpp"

#include <vector>

class IFrontend
{
  public:
    virtual ~IFrontend() = default;

    virtual void PollEvent(Cabe::EventPayload& event) = 0;
    virtual bool IsRunning() = 0;
    virtual void RenderContent(const std::vector<Cabe::File>& files) = 0;
};
