#pragma once

namespace Cabe {

class FileManager;
class KeyPressEvent;
class KeyReleaseEvent;
class OpenFileEvent;
class TextInputEvent;
class QuitEvent;

class EventManager
{
  public:
    void Handle(const KeyPressEvent& event);
    void Handle(const KeyReleaseEvent& event);
    void Handle(const OpenFileEvent& event);
    void Handle(const TextInputEvent& event);
    void Handle(const QuitEvent& event);

    EventManager(FileManager& file_manager)
      : m_FileManager{ file_manager }
    {
    }

    ~EventManager() = default;

    FileManager& m_FileManager;
};

}