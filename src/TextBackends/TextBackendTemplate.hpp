#pragma once

#include "Core/ITextBackend.hpp"
#include <memory>

#define CABE_TEXT_BACKEND_TEMPLATE                                             \
  public:                                                                      \
    void Populate(const std::string& content) override;                        \
    std::string Dump() override;

#define CABE_TEXT_BACKEND_TEMPLATE_CREATOR(name)                               \
    inline std::unique_ptr<Cabe::ITextBackend> createTextBackend()             \
    {                                                                          \
        return std::make_unique<name>();                                       \
    }

#define CABE_TEXT_BACKEND_LOG_INFO(...)                                        \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Info,                                 \
                   Cabe::Log::ELogCategory::TextBackend,                       \
                   __VA_ARGS__)

#define CABE_TEXT_BACKEND_LOG_WARN(...)                                        \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Warn,                                 \
                   Cabe::Log::ELogCategory::TextBackend,                       \
                   __VA_ARGS__)

#define CABE_TEXT_BACKEND_LOG_ERROR(...)                                       \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Error,                                \
                   Cabe::Log::ELogCategory::TextBackend,                       \
                   __VA_ARGS__)