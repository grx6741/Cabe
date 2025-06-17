#pragma once

#include "Log.hpp"

namespace Cabe {

static std::stringstream s_LogStream;

}
#define CABE_LOG_INFO(...)                                                     \
    Cabe::Log(Cabe::s_LogStream, Cabe::ELogLevel::INFO, __VA_ARGS__)
#define CABE_LOG_WARN(...)                                                     \
    Cabe::Log(Cabe::s_LogStream, Cabe::ELogLevel::WARN, __VA_ARGS__)
#define CABE_LOG_ERROR(...)                                                    \
    Cabe::Log(Cabe::s_LogStream, Cabe::ELogLevel::ERROR, __VA_ARGS__)
#define CABE_LOG_CRITICAL(...)                                                 \
    Cabe::Log(Cabe::s_LogStream, Cabe::ELogLevel::CRITICAL, __VA_ARGS__)

#define CABE_TODO                                                              \
    do {                                                                       \
        CABE_LOG_WARN(                                                         \
          "%s:%d %s is not implemented\n", __FILE__, __LINE__, __func__);      \
    } while (0)

#define CABE_MEM_CHECK(p)                                                      \
    do {                                                                       \
        if (!(p))                                                              \
            CABE_LOG_CRITICAL("Memory Allocation Failed! Not Enough RAM?");    \
    } while (0)
