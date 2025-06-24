#pragma once

#include <vector>
#include <filesystem>
#include <unordered_map>

#include "Core/File.hpp"
#include "Core/ITextBackend.hpp"

namespace Cabe {

class FileManager
{
  public:
    FileManager();
    ~FileManager();

    void OpenFile(const std::filesystem::path& file_path);
    void OpenFiles(const std::vector<std::filesystem::path>& file_paths);
    // void ProcessEvent(const Cabe::EventPayload& event);

    std::vector<File> GetContent();

  private:
    // void handleEventTextInput(const Cabe::EventPayload& event);
    // void handleEventKeyUp(const Cabe::EventPayload& event);
    // void handleEventKeyDown(const Cabe::EventPayload& event);
    // void handleEventOpenFile(const Cabe::EventPayload& event);
    // void handleEventSaveFile(const Cabe::EventPayload& event);
    // void handleEventQuit(const Cabe::EventPayload& event);

  private:
    std::unordered_map<std::string, std::unique_ptr<ITextBackend>> m_FileHandles;

    std::unordered_map<std::string, std::unique_ptr<ITextBackend>>::iterator
      m_CurrentTextHandlerIndex;
};

} // namespace Cabe