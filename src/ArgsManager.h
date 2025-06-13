#pragma once

#include "Utils.h"

namespace Cabe
{

class ArgsManager
{
  public:
    ArgsManager(int argc, char **argv);
    ~ArgsManager();

  private:
    void parseConfigValue(const char *config_value_pair);
    void parseFileName(const char *file_name);

  private:
    std::vector<std::string> m_FileNames;
    std::unordered_map<std::string, std::string> m_Config;
};

} // namespace Cabe