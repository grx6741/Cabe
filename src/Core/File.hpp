#pragma once

#include <string>

namespace Cabe {

class File
{
    std::string name;
    std::string content; // TODO : Later change it to treesitter's AST

  public:
    File()
      : name("")
      , content("")
    {
    }
    File(const std::string& name, const std::string& content)
      : name(name)
      , content(content)
    {
    }
    File(const File& other)
      : name(other.name)
      , content(other.content)
    {
    }
    ~File() = default;

    File(File&&) = default;
    File& operator=(const File&) = default;
    File& operator=(File&&) = default;

    inline const std::string& GetName() const { return name; }
    inline const std::string& GetContent() const { return content; }

    inline void SetName(const std::string& name) { this->name = name; }
    inline void SetContent(const std::string& content)
    {
        this->content = content;
    }
};

} // namespace Cabe