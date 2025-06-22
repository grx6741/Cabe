#pragma once

#include "Frontends/FrontendTemplate.hpp"

#include <SDL3/SDL.h>

class SDL3BuiltInFrontend : public Cabe::IFrontend
{
    CABE_FRONTEND_TEMPLATE;

  public:
    SDL3BuiltInFrontend();
    ~SDL3BuiltInFrontend() override;

  private:
    bool handleQuitEvent(SDL_Event& sdl_event, Cabe::EventPayload& event);
    bool handleKeyboardEvent(SDL_Event& sdl_event, Cabe::EventPayload& event);

    void openFileDialog(Cabe::EventPayload& event);

    Cabe::EKey getKeyFromKey(const SDL_Keycode& key_code);
    Cabe::EKeyMod getModFromKey(const SDL_Keymod& key_mod);

  private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_RenderTarget;

    bool m_Quit{ false };
    Uint32 m_WindowWidth{ 640 };
    Uint32 m_WindowHeight{ 480 };
};

CABE_FRONTEND_TEMPLATE_CREATOR(SDL3BuiltInFrontend);

std::string GetModName(const SDL_Keymod mod);