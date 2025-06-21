#include "FileManager.hpp"
#include "Backend.hpp"
#include "Utils.hpp"

#include <fstream>

namespace Cabe {

FileManager::FileManager()
  : m_CurrentTextHandlerIndex(m_FileHandles.end())
{
    CABE_LOG_INFO("FileManager initialized");
}

FileManager::~FileManager()
{
    CABE_LOG_WARN("FileManager destroyed");
}

void
FileManager::OpenFile(const std::filesystem::path& file_path)
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

    auto& entry = m_FileHandles[file_path.filename().string()];

    entry = createBackend();
    entry->Populate(file_content.str());

    m_CurrentTextHandlerIndex =
      m_FileHandles.find(file_path.filename().string());
}

void
FileManager::OpenFiles(const std::vector<std::filesystem::path>& file_paths)
{
    for (const auto& file_path : file_paths) {
        OpenFile(file_path);
    }
}

void
FileManager::ProcessEvent(const Cabe::EventPayload event)
{
    switch (event.type) {
        case Cabe::EEventType::TEXT_INPUT:
            CABE_LOG_INFO("Text input: %s",
                          std::get<std::string>(event.data).c_str());
            break;
        case Cabe::EEventType::KEY_UP:
            CABE_LOG_INFO("Key up: %d",
                          std::get<Cabe::KeyboardInput>(event.data).direction);
            break;
        case Cabe::EEventType::KEY_DOWN:
            CABE_LOG_INFO("Key down: %d",
                          std::get<Cabe::KeyboardInput>(event.data).direction);
            break;
        case Cabe::EEventType::OPEN_FILE:
            CABE_LOG_INFO("Open file");
            break;
        case Cabe::EEventType::SAVE_FILE:
            CABE_LOG_INFO("Save file");
            break;
        case Cabe::EEventType::QUIT:
            CABE_LOG_INFO("Quit");
            break;
        case Cabe::EEventType::NONE:
            CABE_LOG_INFO("None");
            break;
    }

    m_CurrentTextHandlerIndex->second->ProcessEvent(event);
}

std::vector<File>
FileManager::GetContent()
{
    std::vector<File> files;
    files.reserve(m_FileHandles.size());

    for (const auto& file : m_FileHandles) {
        files.push_back(File{ file.first, file.second->Dump() });
    }

    return files;
}

} // namespace Cabe
