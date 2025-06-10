#pragma once
#include <string>

#include "text/Text.h"

class File {
   public:
    File(const char* file_path);

    inline const std::string& GetFilePath() const { return m_Path; }
    inline const std::string& GetContent() const { return m_Text.GetContent(); }

   private:
    std::string m_Path;
    Text m_Text;
};