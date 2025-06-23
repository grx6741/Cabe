#pragma once

#include "RenderBackends/RenderBackendTemplate.hpp"

#include <SDL3/SDL.h>

class SDL3BuiltInRenderBackend : public Cabe::IRenderBackend
{
    CABE_FRONTEND_TEMPLATE;

  public:
    SDL3BuiltInRenderBackend();
    ~SDL3BuiltInRenderBackend() override;

  private:
    std::optional<std::unique_ptr<Cabe::IEvent>> handleQuitEvent(
      SDL_Event& sdl_event);
    std::optional<std::unique_ptr<Cabe::IEvent>> handleKeyboardEvent(
      SDL_Event& sdl_event);

    std::optional<std::unique_ptr<Cabe::IEvent>> openFileDialog();

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

CABE_FRONTEND_TEMPLATE_CREATOR(SDL3BuiltInRenderBackend);

std::string
GetModName(const SDL_Keymod mod);