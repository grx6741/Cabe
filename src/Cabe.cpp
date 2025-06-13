#include "Cabe.h"

#include "Utils.h"

namespace Cabe
{

GlobalState &GlobalState::GetContext()
{
    static GlobalState m_Instance;
    return m_Instance;
}

GlobalState::GlobalState()
{
    bool success = SDL_Init(SDL_INIT_VIDEO);
    if (!success)
    {
        CABE_LOG("Could not initialize SDL. Reason : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    m_Window = SDL_CreateWindow("Cabe", 1920, 1080, SDL_WINDOW_RESIZABLE);
    if (!m_Window)
    {
        CABE_LOG("Could not Create a Window. Reason : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

GlobalState::~GlobalState()
{
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

} // namespace Cabe