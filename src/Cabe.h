#pragma once

#include "SDL3/SDL.h"

namespace Cabe
{

class GlobalState
{
  public:
    static GlobalState &GetContext();

  private:
    GlobalState();
    ~GlobalState();

  private:
    static GlobalState m_Instance;

    SDL_Window* m_Window;
};

} // namespace Cabe