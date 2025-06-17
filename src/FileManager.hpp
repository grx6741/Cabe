#pragma once

#include "IBackend.hpp"
#include "IBackendFactory.hpp"

#include <vector>

namespace Cabe {
class FileManager
{
  public:
    FileManager(std::unique_ptr<IBackendFactory> backend_factory);
    ~FileManager();

    void OpenFile(const std::string& file_path);
    void OpenFiles(const std::vector<std::string>& file_paths);
    void ProcessEvent(const Cabe::EventPayload event);

    // temporary
    std::vector<std::string> GetContent();

  private:
    std::vector<std::unique_ptr<IBackend>> m_FileHandles;
    std::unique_ptr<IBackendFactory> m_BackendFactory;

    int32_t m_CurrentTextHandlerIndex;
};
} // namespace Cabe
