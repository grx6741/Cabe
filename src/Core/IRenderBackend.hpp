#pragma once

#include "Core/Event.hpp"
#include "Core/File.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace Cabe {

class IRenderBackend
{
  public:
    virtual ~IRenderBackend() = default;

    virtual std::optional<std::unique_ptr<IEvent>> PollEvent() = 0;
    virtual bool IsRunning() = 0;
    virtual void RenderContent(const std::vector<Cabe::File>& files) = 0;
};

} // namespace Cabe
