#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdarg.h>

#include "Log.hpp"

#define CABE_LOG_INFO(...)                                                     \
    Cabe::Log::Msg(                                                            \
      Cabe::Log::ELogLevel::Info, Cabe::Log::ELogCategory::Core, __VA_ARGS__)
#define CABE_LOG_WARN(...)                                                     \
    Cabe::Log::Msg(                                                            \
      Cabe::Log::ELogLevel::Warn, Cabe::Log::ELogCategory::Core, __VA_ARGS__)
#define CABE_LOG_ERROR(...)                                                    \
    Cabe::Log::Msg(                                                            \
      Cabe::Log::ELogLevel::Error, Cabe::Log::ELogCategory::Core, __VA_ARGS__)

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

#define CABE_BIT(x) (1 << (x))