#include <SDL3/SDL.h>

#include "SDL3BuiltInFrontEnd.hpp"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include "Utils.hpp"

SDL3BuiltInFrontEnd::SDL3BuiltInFrontEnd()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        CABE_LOG_CRITICAL("Couldn't initialize SDL: %s", SDL_GetError());
        m_Quit = true;
        return;
    }

    if (!SDL_CreateWindowAndRenderer("examples/CATEGORY/NAME",
                                     m_WindowWidth,
                                     m_WindowHeight,
                                     SDL_WINDOW_RESIZABLE,
                                     &m_Window,
                                     &m_Renderer)) {
        CABE_LOG_CRITICAL("Couldn't create window/renderer: %s",
                          SDL_GetError());
        m_Quit = true;
        return;
    }

    SDL_SetRenderVSync(m_Renderer, 1);

    m_RenderTarget = SDL_CreateTexture(m_Renderer,
                                       SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET,
                                       m_WindowWidth,
                                       m_WindowHeight);

    // setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // theme
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(m_Window, m_Renderer);
    ImGui_ImplSDLRenderer3_Init(m_Renderer);
}

SDL3BuiltInFrontEnd::~SDL3BuiltInFrontEnd()
{
    SDL_DestroyTexture(m_RenderTarget);
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
}

void
SDL3BuiltInFrontEnd::PollEvent(Cabe::EventPayload& event)
{
    SDL_Event sdl_event;
    if (!SDL_WaitEvent(&sdl_event)) {
        CABE_LOG_ERROR("Failed to wait for SDL event: %s", SDL_GetError());
    }

    ImGui_ImplSDL3_ProcessEvent(&sdl_event);

    CABE_LOG_INFO("Received SDL event type: %u", sdl_event.type);

    handleQuitEvent(sdl_event, event);

    handleKeyboardEvent(sdl_event, event);
}

bool
SDL3BuiltInFrontEnd::IsRunning()
{
    return !m_Quit;
}

void
SDL3BuiltInFrontEnd::RenderContent(const std::vector<std::string>& content)
{
    SDL_Texture* old_render_target = SDL_GetRenderTarget(m_Renderer);
    SDL_SetRenderTarget(m_Renderer, m_RenderTarget);

    // Draw to Render Target here

    SDL_RenderClear(m_Renderer);

    SDL_SetRenderTarget(m_Renderer, old_render_target);

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    for (const auto& file : content) {
        ImGui::Begin("File Name");
        ImGui::BeginChild("EditorRegion",
                          ImVec2(0, 0),
                          true,
                          ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::TextUnformatted(file.c_str());
        ImGui::EndChild();
        ImGui::End();
    }

    // for (const auto& file : s_EditorState.opened_files) {
    //     ImGui::Begin(file.GetFilePath().c_str());
    //     ImGui::Text("%s", file.GetContent().c_str());
    //     ImGui::End();
    // }

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

void
SDL3BuiltInFrontEnd::handleQuitEvent(SDL_Event& sdl_event,
                                     Cabe::EventPayload& event)
{
    if (sdl_event.type == SDL_EVENT_QUIT) {
        CABE_LOG_INFO("Quit event detected");
        event.type = Cabe::EEventType::QUIT;
        m_Quit = true;
    }
}

void
SDL3BuiltInFrontEnd::handleKeyboardEvent(SDL_Event& sdl_event,
                                         Cabe::EventPayload& event)
{
    switch (sdl_event.type) {
        case SDL_EVENT_TEXT_INPUT: {
            event.type = Cabe::EEventType::TEXT_INPUT;
            event.data = std::string(sdl_event.text.text);
            CABE_LOG_INFO("Text input: %s", sdl_event.text.text);
            break;
        }

        case SDL_EVENT_KEY_DOWN: {
            event.type = Cabe::EEventType::KEY_DOWN;
            event.data =
              Cabe::KeyboardInput{ getDirectionFromKey(sdl_event.key.key),
                                   getModFromKey(sdl_event.key.mod) };
            CABE_LOG_INFO(
              "Key down: key=%d mod=%d", sdl_event.key.key, sdl_event.key.mod);
            break;
        }

        case SDL_EVENT_KEY_UP: {
            event.type = Cabe::EEventType::KEY_UP;
            event.data =
              Cabe::KeyboardInput{ getDirectionFromKey(sdl_event.key.key),
                                   getModFromKey(sdl_event.key.mod) };
            CABE_LOG_INFO(
              "Key up: key=%d mod=%d", sdl_event.key.key, sdl_event.key.mod);
            break;
        }

        default:
            break;
    }
}

Cabe::EKeyDirection
SDL3BuiltInFrontEnd::getDirectionFromKey(const SDL_Keycode& key_code)
{
    switch (key_code) {
        case SDLK_LEFT:
            return Cabe::EKeyDirection::ARROW_LEFT;
        case SDLK_RIGHT:
            return Cabe::EKeyDirection::ARROW_RIGHT;
        case SDLK_UP:
            return Cabe::EKeyDirection::ARROW_UP;
        case SDLK_DOWN:
            return Cabe::EKeyDirection::ARROW_DOWN;
    }

    return Cabe::EKeyDirection::NONE;
}

Cabe::EKeyMod
SDL3BuiltInFrontEnd::getModFromKey(const SDL_Keymod& key_mod)
{
    if (key_mod & SDL_KMOD_CTRL)
        return Cabe::EKeyMod::CTRL;
    if (key_mod & SDL_KMOD_SHIFT)
        return Cabe::EKeyMod::SHIFT;
    if (key_mod & SDL_KMOD_ALT)
        return Cabe::EKeyMod::ALT;

    return Cabe::EKeyMod::NONE;
}
