#pragma once

#include "Core/Events/KeyEvent.hpp"
#include "Core/Events/OpenFileEvent.hpp"
#include "Core/Events/QuitEvent.hpp"
#include "Core/Events/TextInputEvent.hpp"
#include "Core/IRenderBackend.hpp"

#include <memory>

#define CABE_FRONTEND_TEMPLATE                                                 \
  public:                                                                      \
    std::optional<std::unique_ptr<Cabe::IEvent>> PollEvent() override;         \
    bool IsRunning() override;                                                 \
    void RenderContent(const std::vector<Cabe::File>& files) override;

#define CABE_FRONTEND_TEMPLATE_CREATOR(name)                                   \
    inline std::unique_ptr<Cabe::IRenderBackend> createRenderBackend()         \
    {                                                                          \
        return std::make_unique<name>();                                       \
    }

#define CABE_FRONTEND_LOG_INFO(...)                                            \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Info,                                 \
                   Cabe::Log::ELogCategory::RenderBackend,                     \
                   __VA_ARGS__)

#define CABE_FRONTEND_LOG_WARN(...)                                            \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Warn,                                 \
                   Cabe::Log::ELogCategory::RenderBackend,                     \
                   __VA_ARGS__)

#define CABE_FRONTEND_LOG_ERROR(...)                                           \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Error,                                \
                   Cabe::Log::ELogCategory::RenderBackend,                     \
                   __VA_ARGS__)