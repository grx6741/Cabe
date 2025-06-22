#pragma once

#include "Core/IFrontend.hpp"
#include <memory>

#define CABE_FRONTEND_TEMPLATE                                                 \
  public:                                                                      \
    void PollEvent(Cabe::EventPayload& event) override;                        \
    bool IsRunning() override;                                                 \
    void RenderContent(const std::vector<Cabe::File>& files) override;

#define CABE_FRONTEND_TEMPLATE_CREATOR(name)                                   \
    inline std::unique_ptr<Cabe::IFrontend> createFrontend()                   \
    {                                                                          \
        return std::make_unique<name>();                                       \
    }

#define CABE_FRONTEND_LOG_INFO(...)                                            \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Info,                                 \
                   Cabe::Log::ELogCategory::Frontend,                          \
                   __VA_ARGS__)

#define CABE_FRONTEND_LOG_WARN(...)                                            \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Warn,                                 \
                   Cabe::Log::ELogCategory::Frontend,                          \
                   __VA_ARGS__)

#define CABE_FRONTEND_LOG_ERROR(...)                                           \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Error,                                \
                   Cabe::Log::ELogCategory::Frontend,                          \
                   __VA_ARGS__)