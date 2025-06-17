#pragma once

#include <sstream>

namespace Cabe {

enum class ELogLevel
{
    VERBOSE,
    INFO,
    WARN,
    ERROR,
    CRITICAL
};

void
Log(std::stringstream& stream, ELogLevel level, const char* fmt, ...);

} // namespace Cabe
