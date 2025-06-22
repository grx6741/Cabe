#pragma once

#include "Core/IBackend.hpp"
#include <memory>

#define CABE_BACKEND_TEMPLATE                                                  \
  public:                                                                      \
    void Populate(const std::string& content) override;                        \
    std::string Dump() override;

#define CABE_BACKEND_TEMPLATE_CREATOR(name)                                    \
    inline std::unique_ptr<Cabe::IBackend> createBackend()                           \
    {                                                                          \
        return std::make_unique<name>();                                       \
    }

#define CABE_BACKEND_LOG_INFO(...)                                             \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Info,                                 \
                   Cabe::Log::ELogCategory::Backend,                           \
                   __VA_ARGS__)

#define CABE_BACKEND_LOG_WARN(...)                                             \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Warn,                                 \
                   Cabe::Log::ELogCategory::Backend,                           \
                   __VA_ARGS__)

#define CABE_BACKEND_LOG_ERROR(...)                                            \
    Cabe::Log::Msg(Cabe::Log::ELogLevel::Error,                                \
                   Cabe::Log::ELogCategory::Backend,                           \
                   __VA_ARGS__)