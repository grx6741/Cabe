#include <SDL3/SDL.h>

#include "Frontend.hpp"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include "Utils.hpp"

SDL3BuiltInFrontend::SDL3BuiltInFrontend()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        CABE_LOG_ERROR("Couldn't initialize SDL: %s", SDL_GetError());
        m_Quit = true;
        return;
    }

    if (!SDL_CreateWindowAndRenderer("examples/CATEGORY/NAME",
                                     m_WindowWidth,
                                     m_WindowHeight,
                                     SDL_WINDOW_RESIZABLE,
                                     &m_Window,
                                     &m_Renderer)) {
        CABE_LOG_ERROR("Couldn't create window/renderer: %s", SDL_GetError());
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

SDL3BuiltInFrontend::~SDL3BuiltInFrontend()
{
    SDL_DestroyTexture(m_RenderTarget);
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
}

void
SDL3BuiltInFrontend::PollEvent(Cabe::EventPayload& event)
{
    SDL_Event sdl_event;
    if (!SDL_WaitEvent(&sdl_event)) {
        CABE_LOG_ERROR("Failed to wait for SDL event: %s", SDL_GetError());
    }

    ImGui_ImplSDL3_ProcessEvent(&sdl_event);

    // CABE_LOG_INFO("Received SDL event type: %u", sdl_event.type);

    if (handleQuitEvent(sdl_event, event)) {
        return;
    }

    if (handleKeyboardEvent(sdl_event, event)) {
        return;
    }
}

bool
SDL3BuiltInFrontend::IsRunning()
{
    return !m_Quit;
}

void
SDL3BuiltInFrontend::RenderContent(const std::vector<Cabe::File>& files)
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

    for (const auto& file : files) {
        ImGui::Begin(file.name.c_str());
        ImGui::BeginChild("EditorRegion",
                          ImVec2(0, 0),
                          true,
                          ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::TextUnformatted(file.content.c_str());
        ImGui::EndChild();
        ImGui::End();
    }

    // Logs
    std::string log;
    Cabe::Log::LogToString(log);

    ImGui::Begin("Logs");
    ImGui::TextUnformatted(log.c_str());
    ImGui::End();

    // for (const auto& file : s_EditorState.opened_files) {
    //     ImGui::Begin(file.GetFilePath().c_str());
    //     ImGui::Text("%s", file.GetContent().c_str());
    //     ImGui::End();
    // }

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

bool
SDL3BuiltInFrontend::handleQuitEvent(SDL_Event& sdl_event,
                                     Cabe::EventPayload& event)
{
    if (sdl_event.type == SDL_EVENT_QUIT) {
        CABE_LOG_INFO("Quit event detected");
        event.type = Cabe::EEventType::Quit;
        m_Quit = true;

        return true;
    }

    return false;
}

bool
SDL3BuiltInFrontend::handleKeyboardEvent(SDL_Event& sdl_event,
                                         Cabe::EventPayload& event)
{
    switch (sdl_event.type) {
        case SDL_EVENT_TEXT_INPUT: {
            event.type = Cabe::EEventType::TextInput;
            event.data = std::string(sdl_event.text.text);
            CABE_LOG_INFO("Text input: %s", sdl_event.text.text);
            return true;
        }

        case SDL_EVENT_KEY_DOWN: {
            if (sdl_event.key.mod & SDL_KMOD_CTRL) {
                if (sdl_event.key.key == SDLK_O) {
                    openFileDialog(event);
                }
            } else {
                event.type = Cabe::EEventType::KeyDown;
                event.data =
                  Cabe::KeyboardInput{ getKeyFromKey(sdl_event.key.key),
                                       getModFromKey(sdl_event.key.mod) };
            }
            // CABE_LOG_INFO("Key down: key=%d mod=%d", sdl_event.key.key,
            // sdl_event.key.mod);

            return true;
        }

        case SDL_EVENT_KEY_UP: {
            event.type = Cabe::EEventType::KeyUp;
            event.data =
              Cabe::KeyboardInput{ getKeyFromKey(sdl_event.key.key),
                                   getModFromKey(sdl_event.key.mod) };
            // CABE_LOG_INFO("Key up: key=%d mod=%d", sdl_event.key.key,
            // sdl_event.key.mod);

            return true;
        }

        default:
            break;
    }

    return false;
}

void
SDL3BuiltInFrontend::openFileDialog(Cabe::EventPayload& event)
{
    struct _userData
    {
        Cabe::EventPayload* event;
        bool handled;
    } userdata = { &event, false };

    SDL_ShowOpenFileDialog(
      [](void* userdata, const char* const* filelist, int filter) {
          _userData* data = static_cast<_userData*>(userdata);
          auto event = data->event;
          auto& handled = data->handled;

          if (!filelist || !(*filelist)) {
              // No files selected
              event->type = Cabe::EEventType::None;
              handled = true;
              return;
          }

          event->type = Cabe::EEventType::OpenFile;
          event->data = std::vector<std::filesystem::path>{};
          auto& files =
            std::get<std::vector<std::filesystem::path>>(event->data);
          while (*filelist) {
              files.emplace_back(*filelist);
              ++filelist;
          }

          handled = true;
      },
      static_cast<void*>(&userdata),
      m_Window,
      NULL,
      0,
      NULL,
      true);

    // Wait for the user to select a file
    while (!userdata.handled) {
        SDL_PumpEvents();
        SDL_Delay(1);
    }
}

Cabe::EKey
SDL3BuiltInFrontend::getKeyFromKey(const SDL_Keycode& key_code)
{
    switch (key_code) {
#define CASE(sdl_key, cabe_key)                                                \
    case sdl_key:                                                              \
        return Cabe::EKey::cabe_key
        CASE(SDLK_LEFT, CursorLeft);
        CASE(SDLK_RIGHT, CursorRight);
        CASE(SDLK_UP, CursorUp);
        CASE(SDLK_DOWN, CursorDown);
#undef CASE
    }

    return Cabe::EKey::None;
}

Cabe::EKeyMod
SDL3BuiltInFrontend::getModFromKey(const SDL_Keymod& key_mod)
{
    if (key_mod & SDL_KMOD_CTRL)
        return Cabe::EKeyMod::CTRL;
    if (key_mod & SDL_KMOD_SHIFT)
        return Cabe::EKeyMod::SHIFT;
    if (key_mod & SDL_KMOD_ALT)
        return Cabe::EKeyMod::ALT;

    return Cabe::EKeyMod::NONE;
}
