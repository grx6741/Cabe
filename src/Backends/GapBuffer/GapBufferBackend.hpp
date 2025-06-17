#pragma once

#include "../../Common/IBackEnd.hpp"

class GapBufferBackend : public IBackend
{
  public:
    ~GapBufferBackend() override = default;

    void OpenFile(const std::string& path) override;
    void OpenFiles(const std::vector<std::string>& paths) override;
    void ProcessEvent(const Cabe::EventPayload event) override;
    std::string Dump() override;
};