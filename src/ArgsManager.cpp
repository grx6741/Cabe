#include "ArgsManager.h"

namespace Cabe
{

// Public

ArgsManager::ArgsManager(int argc, char **argv)
{
    // TODO : can only handle --a=1 but not --a= 1 or --a == 1
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
            parseFileName(argv[i]);
        else
            parseConfigValue(argv[i]);
    }
}

ArgsManager::~ArgsManager()
{
}

// Private

void ArgsManager::parseConfigValue(const char *config_value_pair)
{
    std::string_view sv(config_value_pair);

    if (!sv.starts_with("--") || sv.size() < 5)
    {
        CABE_LOG_DEBUG("Invalid Config Argument %s", config_value_pair);
        return;
    }

    sv.remove_prefix(2); // remove "--"

    size_t equal_pos = sv.find('=');
    if (equal_pos == std::string_view::npos)
    {
        CABE_LOG_DEBUG("Invalid Config Argument %s", config_value_pair);
        return;
    }

    std::string key = std::string(sv.substr(0, equal_pos));
    std::string value = std::string(sv.substr(equal_pos + 1));

    m_Config[key] = value;
}

void ArgsManager::parseFileName(const char *file_name)
{
    m_FileNames.push_back(file_name);
}

} // namespace Cabe