#include "IBackendFactory.hpp"

#include "Backends/Basic/BasicBackendFactory.hpp"
#include "FrontEnds/SDL3BuiltIn/SDL3BuiltInFrontEnd.hpp"

#include "FileManager.hpp"

#include "Utils.hpp"

int
main(int argc, char* argv[])
{
    Cabe::s_LogStream = std::stringstream();

    Cabe::FileManager fileManager(std::make_unique<BasicBackendFactory>());
    fileManager.OpenFile(".clang-format");

    std::unique_ptr<IFrontEnd> frontend =
      std::make_unique<SDL3BuiltInFrontEnd>();

    while (frontend->IsRunning()) {

        Cabe::EventPayload event;
        frontend->PollEvent(event);

        fileManager.ProcessEvent(event);

        auto content = fileManager.GetContent();

        frontend->RenderContent(content);
    }

    return 0;
}
