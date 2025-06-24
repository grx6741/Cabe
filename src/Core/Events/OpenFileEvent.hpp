#pragma once

#include "Core/Event.hpp"

#include <filesystem>
#include <vector>

namespace Cabe {

class OpenFileEvent : public IEvent
{
  public:
    inline OpenFileEvent(const std::vector<std::filesystem::path>& files)
      : m_Files{ files }
      , IEvent{ EEventType::OpenFile }
    {
    }

    inline OpenFileEvent()
      : OpenFileEvent{ {} }
    {
    }

    ~OpenFileEvent() override = default;

    inline const std::vector<std::filesystem::path>& GetFiles() const
    {
        return m_Files;
    }
    inline void SetFiles(const std::vector<std::filesystem::path>& files)
    {
        m_Files = files;
    }

    inline void Dispatch(EventManager& event_manager) const override
    {
        event_manager.Handle(*this);
    }

  private:
    std::vector<std::filesystem::path> m_Files;
};

} // namespace Cabe