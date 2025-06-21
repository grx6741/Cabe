#pragma once

#include "IFrontend.hpp"

#include <SDL3/SDL.h>

class SDL3BuiltInFrontend : public IFrontend
{
  public:
    SDL3BuiltInFrontend();
    ~SDL3BuiltInFrontend() override;

    void PollEvent(Cabe::EventPayload& event) override;
    bool IsRunning() override;
    void RenderContent(const std::vector<Cabe::File>& files) override;

  private:
    void handleQuitEvent(SDL_Event& sdl_event, Cabe::EventPayload& event);
    void handleKeyboardEvent(SDL_Event& sdl_event, Cabe::EventPayload& event);

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

std::unique_ptr<IFrontend>
createFrontend();