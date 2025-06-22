#include "Cabe.hpp"

#include "Frontend.hpp"

int
main(int argc, char* argv[])
{
    Cabe::FileManager fileManager;

    std::unique_ptr<Cabe::IFrontend> frontend = createFrontend();

    while (frontend->IsRunning()) {
        Cabe::EventPayload event;
        frontend->PollEvent(event);

        fileManager.ProcessEvent(event);

        auto content = fileManager.GetContent();

        frontend->RenderContent(content);
    }

    Cabe::Log::LogToFile("log.txt");

    return 0;
}
