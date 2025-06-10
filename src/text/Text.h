#pragma once

#include <string>

class Text {
   public:
    Text();

    void Populate(char* data);

    inline const std::string& GetContent() const { return m_Content; }

   private:
    std::string m_Content;
};