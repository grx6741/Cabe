#include "FileManager.hpp"
#include "TextBackend.hpp"
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

    entry = createTextBackend();
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

std::vector<File>
FileManager::GetContent()
{
    std::vector<File> files;
    files.reserve(m_FileHandles.size());

    for (const auto& file : m_FileHandles) {
        files.emplace_back(file.first, file.second->Dump());
    }

    return files;
}

// void
// FileManager::ProcessEvent(const Cabe::EventPayload& event)
// {
//     switch (event.type) {
// #define CASE(e) \
//     case Cabe::EEventType::e: \
//         handleEvent##e(event); \
//         CABE_LOG_INFO("[" #e "] event detected"); \ break;

//         CASE(TextInput)
//         CASE(KeyUp)
//         CASE(KeyDown)
//         CASE(OpenFile)
//         CASE(SaveFile)
//         CASE(Quit)

// #undef CASE
//         case Cabe::EEventType::None:
//             // CABE_LOG_WARN("Unknown event type: %d",
//             // static_cast<int>(event.type));
//             break;
//     }
// }

// // private

// void
// FileManager::handleEventTextInput(const Cabe::EventPayload& event)
// {
// }

// void
// FileManager::handleEventKeyUp(const Cabe::EventPayload& event)
// {
// }

// void
// FileManager::handleEventKeyDown(const Cabe::EventPayload& event)
// {
// }

// void
// FileManager::handleEventOpenFile(const Cabe::EventPayload& event)
// {
//     auto file_names =
//     std::get<std::vector<std::filesystem::path>>(event.data);
//     OpenFiles(file_names);
// }

// void
// FileManager::handleEventSaveFile(const Cabe::EventPayload& event)
// {
// }

// void
// FileManager::handleEventQuit(const Cabe::EventPayload& event)
// {
// }

} // namespace Cabe
