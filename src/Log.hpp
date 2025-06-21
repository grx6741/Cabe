#pragma once

#include <sstream>
#include <stdarg.h>
#include <iostream>

namespace Cabe {

class Log
{
  public:
    enum class ELogLevel
    {
        INFO,
        WARN,
        ERROR,
    };

    inline static void Msg(ELogLevel level, const char* fmt, ...)
    {

        switch (level) {
#define CASE(level)                                                            \
    case ELogLevel::level:                                                     \
        m_Stream << "[" #level "] ";                                           \
        break;

            CASE(INFO)
            CASE(WARN)
            CASE(ERROR)

#undef CASE
        }

        char buffer[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        m_Stream << buffer << '\n';
    }

    static inline void LogToConsole(const char* log_file)
    {
        std::cout << m_Stream.rdbuf();
    }

    static inline void LogToString(std::string& log)
    {
        log = m_Stream.str();
    }

  private:
    static std::stringstream m_Stream;
};

} // namespace Cabe