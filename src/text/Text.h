#pragma once

#include <string>

class Text {
   public:
    Text();

    void Populate(const char* data);

    [[nodiscard]] const std::string& GetContent() const { return m_Content; }

   private:
    std::string m_Content;
};