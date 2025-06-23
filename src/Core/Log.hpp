#pragma once

#include "Core/Utils.hpp"

#define CABE_CORE_UNREACHBLE(msg)                                              \
    do {                                                                       \
        CABE_LOG_ERROR("Unreachable @ %s:%d", __FILE__, __LINE__);             \
        assert(0);                                                             \
    } while (0);

namespace Cabe {

class Log
{
  public:
    enum class ELogLevel
    {
        Info,
        Warn,
        Error
    };

    enum class ELogCategory
    {
        RenderBackend,
        Backend,
        Core
    };

    inline static void Msg(ELogLevel level,
                           ELogCategory category,
                           const char* fmt,
                           ...)
    {
        std::stringstream* stream;
        switch (category) {
#define CASE(category)                                                         \
    case ELogCategory::category:                                               \
        stream = &(m_##category##LogStream);                                   \
        break;
            CASE(RenderBackend)
            CASE(Backend)
            CASE(Core)
#undef CASE
        }

        switch (level) {
#define CASE(level)                                                            \
    case ELogLevel::level:                                                     \
        (*stream) << "[" #level "] ";                                          \
        std::cout << "[" #level "] ";                                          \
        break;
            CASE(Info)
            CASE(Warn)
            CASE(Error)
#undef CASE
        }

        char buffer[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        (*stream) << buffer << '\n';
#ifdef DEBUG
        std::cout << buffer << '\n';
#endif
    }

    static inline void LogToFile(const char* log_file)
    {
        std::ofstream file(log_file);
        if (!file.is_open()) {
            std::cerr << "Error Opening Log File";
        }

        file << "---[Core]---\n";
        file << m_CoreLogStream.rdbuf() << '\n';
        file << "---[RenderBackend]---\n";
        file << m_RenderBackendLogStream.rdbuf() << '\n';
        file << "---[Backend]---\n";
        file << m_BackendLogStream.rdbuf() << '\n';

        file.close();
    }

    static inline void LogToString(ELogCategory category, std::string& log)
    {
        std::stringstream* stream;
        switch (category) {
#define CASE(category)                                                         \
    case ELogCategory::category:                                               \
        stream = &(m_##category##LogStream);                                   \
        break;
            CASE(RenderBackend)
            CASE(Backend)
            CASE(Core)
            default:
                stream = &m_CoreLogStream; // Or throw/assert
                break;
#undef CASE
        }

        log = stream->str();
    }

  private:
    static std::stringstream m_CoreLogStream;
    static std::stringstream m_RenderBackendLogStream;
    static std::stringstream m_BackendLogStream;
};

} // namespace Cabe