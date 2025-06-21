#include "Frontend.hpp"

#include "IFrontend.hpp"
#include "FileManager.hpp"

#include <iostream>

#include "Log.hpp"

int
main(int argc, char* argv[])
{
    Cabe::s_LogStream = std::stringstream();

    Cabe::FileManager fileManager;

    std::unique_ptr<IFrontend> frontend = createFrontend();

    while (frontend->IsRunning()) {
        Cabe::EventPayload event;
        frontend->PollEvent(event);

        fileManager.ProcessEvent(event);

        auto content = fileManager.GetContent();

        frontend->RenderContent(content);
    }

    std::cout << Cabe::s_LogStream.str() << '\n';
    return 0;
}
