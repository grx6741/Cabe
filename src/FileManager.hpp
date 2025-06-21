#pragma once

#include "IBackend.hpp"

#include <unordered_map>
#include <filesystem>

namespace Cabe {

    struct File {
        std::string name;
        std::string content; // TODO : Later change it to treesitter's AST
    };

    class FileManager
    {
	public:
	    FileManager();
	    ~FileManager();

	    void OpenFile(const std::filesystem::path& file_path);
	    void OpenFiles(const std::vector<std::filesystem::path>& file_paths);
	    void ProcessEvent(const Cabe::EventPayload& event);

	    // temporary
	    std::vector<File> GetContent();

    private:

    void handleEventTextInput(const Cabe::EventPayload& event);
    void handleEventKeyUp(const Cabe::EventPayload& event);
    void handleEventKeyDown(const Cabe::EventPayload& event);
    void handleEventOpenFile(const Cabe::EventPayload& event);
    void handleEventSaveFile(const Cabe::EventPayload& event);
    void handleEventQuit(const Cabe::EventPayload& event);

	private:
	    std::unordered_map<std::string, std::unique_ptr<IBackend>> m_FileHandles;

	    std::unordered_map<std::string, std::unique_ptr<IBackend>>::iterator m_CurrentTextHandlerIndex;
    };
} // namespace Cabe
