#pragma once

#include "Core/Event.hpp"

#include <vector>
#include <filesystem>

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

    void Dispatch() override;

  private:
    std::vector<std::filesystem::path> m_Files;
};

} // namespace Cabe