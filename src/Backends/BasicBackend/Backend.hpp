#pragma once

#include "IBackend.hpp"

#include <memory>

class BasicBackend : public IBackend
{
  public:
    BasicBackend() = default;
    ~BasicBackend() override = default;

    void Populate(const std::string& content) override;
    void ProcessEvent(const Cabe::EventPayload event) override;
    std::string Dump() override;

  private:
    std::string m_Content;
};

std::unique_ptr<IBackend>
createBackend();