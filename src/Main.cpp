#include "Frontend.hpp"

#include "FileManager.hpp"
#include "Log.hpp"

int
main(int argc, char* argv[])
{
    Cabe::FileManager fileManager;

    std::unique_ptr<IFrontend> frontend = createFrontend();

    while (frontend->IsRunning()) {
        Cabe::EventPayload event;
        frontend->PollEvent(event);

        fileManager.ProcessEvent(event);

        auto content = fileManager.GetContent();

        frontend->RenderContent(content);
    }

    Cabe::Log::LogToConsole("log.txt");

    return 0;
}
