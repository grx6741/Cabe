#pragma once

#include "Core/Events/KeyEvent.hpp"
#include "Core/Events/OpenFileEvent.hpp"
#include "Core/Events/TextInputEvent.hpp"
#include "Core/Events/QuitEvent.hpp"

namespace Cabe {
    class EventManager {
    public:
        inline static EventManager& Get() {
            static EventManager s_Instance;
            return s_Instance;
        }

        void Handle(const KeyPressEvent& event);
        void Handle(const KeyReleaseEvent& event);
        void Handle(const OpenFileEvent& event);
        void Handle(const TextInputEvent& event);
        void Handle(const QuitEvent& event);

    private:
        EventManager() = default;
        ~EventManager() = default;

        static EventManager s_Instance;
    };
}