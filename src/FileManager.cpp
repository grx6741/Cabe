#include "FileManager.hpp"
#include "Utils.hpp"

#include <fstream>

namespace Cabe {

FileManager::FileManager(std::unique_ptr<IBackendFactory> backend_factory)
  : m_BackendFactory(std::move(backend_factory))
  , m_CurrentTextHandlerIndex(-1)
{
    CABE_LOG_INFO("FileManager initialized");
}

FileManager::~FileManager()
{
    CABE_LOG_WARN("FileManager destroyed");
}

void
FileManager::OpenFile(const std::string& file_path)
{
    // TODO : If file Not found, Create a new file with this name
    std::ifstream file(file_path);
    if (!file.is_open()) {
        CABE_LOG_ERROR("Failed to open file: %s", file_path.c_str());
        return;
    }

    std::stringstream file_content;
    file_content << file.rdbuf();

    file.close();

    m_FileHandles.push_back(m_BackendFactory->create());
    m_CurrentTextHandlerIndex = static_cast<int32_t>(m_FileHandles.size() - 1);

    m_FileHandles[m_CurrentTextHandlerIndex]->Populate(file_content.str());
}

void
FileManager::OpenFiles(const std::vector<std::string>& file_paths)
{
    for (const auto& file_path : file_paths) {
        OpenFile(file_path);
    }
}

void
FileManager::ProcessEvent(const Cabe::EventPayload event)
{
    m_FileHandles[m_CurrentTextHandlerIndex]->ProcessEvent(event);
}

std::vector<std::string>
FileManager::GetContent()
{
    std::vector<std::string> content;
    content.reserve(m_FileHandles.size());

    for (const auto& file : m_FileHandles) {
        content.push_back(file->Dump());
    }

    return content;
}

} // namespace Cabe
