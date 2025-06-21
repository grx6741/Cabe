#include "Log.hpp"

#include <cstdarg>

namespace Cabe {

std::stringstream s_LogStream;

void
Log(std::stringstream& stream, ELogLevel level, const char* fmt, ...)
{
    switch (level) {
        case ELogLevel::VERBOSE: stream << "[VERBOSE] "; break;
        case ELogLevel::INFO:    stream << "[INFO] ";    break;
        case ELogLevel::WARN:    stream << "[WARN] ";    break;
        case ELogLevel::ERROR:   stream << "[ERROR] ";   break;
        case ELogLevel::CRITICAL:stream << "[CRITICAL] ";break;
    }

    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    stream << buffer << '\n';
}

} // namespace Cabe
