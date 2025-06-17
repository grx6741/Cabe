#include "Log.hpp"

#include <cstdarg>

namespace Cabe {

void
Log(std::stringstream& stream, ELogLevel level, const char* fmt, ...)
{
    switch (level) {
        case ELogLevel::VERBOSE:
            stream << "[VERBOSE] ";
            break;
        case ELogLevel::INFO:
            stream << "[INFO] ";
            break;
        case ELogLevel::WARN:
            stream << "[WARN] ";
            break;
        case ELogLevel::ERROR:
            stream << "[ERROR] ";
            break;
        case ELogLevel::CRITICAL:
            stream << "[CRITICAL] ";
            break;
    }

    va_list args;
    va_start(args, fmt);
    stream << fmt;
    va_end(args);
}

} // namespace Cabe
