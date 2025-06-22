#pragma once

#include "Core/Event.hpp"
#include "Core/File.hpp"

namespace Cabe {

class IFrontend
{
  public:
    virtual ~IFrontend() = default;

    virtual void PollEvent(Cabe::EventPayload& event) = 0;
    virtual bool IsRunning() = 0;
    virtual void RenderContent(const std::vector<Cabe::File>& files) = 0;
};

} // namespace Cabe
