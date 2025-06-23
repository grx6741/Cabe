#include "Cabe.hpp"

#include "RenderBackend.hpp"

int
main(int argc, char* argv[])
{
    Cabe::FileManager fileManager;

    std::unique_ptr<Cabe::IRenderBackend> frontend = createRenderBackend();

    while (frontend->IsRunning()) {
        auto event = frontend->PollEvent();

        if (event.has_value())
            event.value()->Dispatch();

        auto content = fileManager.GetContent();

        frontend->RenderContent(content);
    }

    Cabe::Log::LogToFile("log.txt");

    return 0;
}
