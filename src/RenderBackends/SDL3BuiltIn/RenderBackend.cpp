#include <SDL3/SDL.h>

#include "RenderBackend.hpp"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include "Core/Utils.hpp"

#define NS_TO_SEC(ns) ((static_cast<float>(ns)) / 1e9)

SDL3BuiltInRenderBackend::SDL3BuiltInRenderBackend()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        CABE_FRONTEND_LOG_ERROR("Couldn't initialize SDL: %s", SDL_GetError());
        m_Quit = true;
        return;
    }

    if (!SDL_CreateWindowAndRenderer("examples/CATEGORY/NAME",
                                     m_WindowWidth,
                                     m_WindowHeight,
                                     SDL_WINDOW_RESIZABLE,
                                     &m_Window,
                                     &m_Renderer)) {
        CABE_FRONTEND_LOG_ERROR("Couldn't create window/renderer: %s",
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

SDL3BuiltInRenderBackend::~SDL3BuiltInRenderBackend()
{
    SDL_DestroyTexture(m_RenderTarget);
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
}

std::optional<std::unique_ptr<Cabe::IEvent>>
SDL3BuiltInRenderBackend::PollEvent()
{
    SDL_Event sdl_event;
    if (!SDL_WaitEvent(&sdl_event)) {
        CABE_FRONTEND_LOG_ERROR("Failed to wait for SDL event: %s",
                                SDL_GetError());
    }

    ImGui_ImplSDL3_ProcessEvent(&sdl_event);

    // CABE_FRONTEND_LOG_INFO("Received SDL event type: %u", sdl_event.type);

    std::optional<std::unique_ptr<Cabe::IEvent>> event;

    event = handleQuitEvent(sdl_event);
    if (event.has_value())
        return std::move(event.value());

    event = handleKeyboardEvent(sdl_event);
    if (event.has_value())
        return std::move(event.value());

    return std::nullopt;
}

bool
SDL3BuiltInRenderBackend::IsRunning()
{
    return !m_Quit;
}

void
SDL3BuiltInRenderBackend::RenderContent(const std::vector<Cabe::File>& files)
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
        ImGui::Begin(file.GetName().c_str());
        ImGui::BeginChild("EditorRegion",
                          ImVec2(0, 0),
                          true,
                          ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::TextUnformatted(file.GetContent().c_str());
        ImGui::EndChild();
        ImGui::End();
    }

    // Logs
    std::string log;
    {
        Cabe::Log::LogToString(Cabe::Log::ELogCategory::RenderBackend, log);
        ImGui::Begin("RenderBackend Logs");
        ImGui::TextUnformatted(log.c_str());
        ImGui::End();
    }

    {
        Cabe::Log::LogToString(Cabe::Log::ELogCategory::Backend, log);
        ImGui::Begin("Text Backend Logs");
        ImGui::TextUnformatted(log.c_str());
        ImGui::End();
    }

    {
        Cabe::Log::LogToString(Cabe::Log::ELogCategory::Core, log);
        ImGui::Begin("Core Logs");
        ImGui::TextUnformatted(log.c_str());
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

std::optional<std::unique_ptr<Cabe::IEvent>>
SDL3BuiltInRenderBackend::handleQuitEvent(SDL_Event& sdl_event)
{
    if (sdl_event.type == SDL_EVENT_QUIT) {
        CABE_FRONTEND_LOG_INFO("{%.2f s} SDL_QUIT Event detected",
                               NS_TO_SEC(sdl_event.quit.timestamp));
        m_Quit = true;

        return std::make_unique<Cabe::QuitEvent>();
    }
    return std::nullopt;
}

std::optional<std::unique_ptr<Cabe::IEvent>>
SDL3BuiltInRenderBackend::handleKeyboardEvent(SDL_Event& sdl_event)
{
    switch (sdl_event.type) {
        case SDL_EVENT_TEXT_INPUT: {
            // event.type = Cabe::EEventType::TextInput;
            // event.data = std::string(sdl_event.text.text);
            CABE_FRONTEND_LOG_INFO(
              "{%*.2f s} SDL_TEXTINPUT Event detected. Text input = %s",
              7,
              NS_TO_SEC(sdl_event.key.timestamp),
              sdl_event.text.text);
            return std::make_unique<Cabe::TextInputEvent>(
              std::string(sdl_event.text.text));
        }

        case SDL_EVENT_KEY_DOWN: {
            CABE_FRONTEND_LOG_INFO(
              "{%*.2f s} SDL_EVENT_KEY_DOWN:  SDL_KEY[%s] | SDL_MOD[%s]",
              7,
              NS_TO_SEC(sdl_event.key.timestamp),
              SDL_GetKeyName(sdl_event.key.key),
              GetModName(sdl_event.key.mod).c_str());
            if (sdl_event.key.mod & SDL_KMOD_CTRL) {
                if (sdl_event.key.key == SDLK_O) {
                    return openFileDialog();
                }
            } else {
                // event.type = Cabe::EEventType::KeyDown;
                // event.data =
                //   Cabe::KeyboardInput{ getKeyFromKey(sdl_event.key.key),
                //                        getModFromKey(sdl_event.key.mod) };
                return std::make_unique<Cabe::KeyPressEvent>(
                  getKeyFromKey(sdl_event.key.key),
                  getModFromKey(sdl_event.key.mod));
            }
        }

        case SDL_EVENT_KEY_UP: {
            CABE_FRONTEND_LOG_INFO(
              "{%*.2f s} SDL_EVENT_KEY_UP:  SDL_KEY[%s] | SDL_MOD[%s]",
              7,
              NS_TO_SEC(sdl_event.key.timestamp),
              SDL_GetKeyName(sdl_event.key.key),
              GetModName(sdl_event.key.mod).c_str());
            return std::make_unique<Cabe::KeyReleaseEvent>(
              getKeyFromKey(sdl_event.key.key),
              getModFromKey(sdl_event.key.mod));
            // event.type = Cabe::EEventType::KeyUp;
            // event.data =
            //   Cabe::KeyboardInput{ getKeyFromKey(sdl_event.key.key),
            //                        getModFromKey(sdl_event.key.mod) };
            // CABE_FRONTEND_LOG_INFO("Key up: key=%d mod=%d",
            // sdl_event.key.key, sdl_event.key.mod);
        }

        default:
            break;
    }

    return std::nullopt;
}

std::optional<std::unique_ptr<Cabe::IEvent>>
SDL3BuiltInRenderBackend::openFileDialog()
{
    struct _userData
    {
        std::vector<std::filesystem::path> files;
        bool handled{ false };
    } userdata;

    SDL_ShowOpenFileDialog(
      [](void* userdata, const char* const* filelist, int filter) {
          _userData* data = static_cast<_userData*>(userdata);
          //   auto event = data->event;
          auto& files = data->files;
          auto& handled = data->handled;

          if (!filelist || !(*filelist)) {
              // No files selected
              //   event->type = Cabe::EEventType::None;
              handled = true;
              return;
          }

          //   event->type = Cabe::EEventType::OpenFile;
          //   event->data = std::vector<std::filesystem::path>{};
          //   auto& files =
          //   std::get<std::vector<std::filesystem::path>>(event->data);

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

    return (userdata.files.size() > 0)
             ? std::make_unique<Cabe::OpenFileEvent>(userdata.files)
             : std::optional<std::unique_ptr<Cabe::IEvent>>{};
}

Cabe::EKey
SDL3BuiltInRenderBackend::getKeyFromKey(const SDL_Keycode& key_code)
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
SDL3BuiltInRenderBackend::getModFromKey(const SDL_Keymod& key_mod)
{
    if (key_mod & SDL_KMOD_CTRL)
        return Cabe::EKeyMod::CTRL;
    if (key_mod & SDL_KMOD_SHIFT)
        return Cabe::EKeyMod::SHIFT;
    if (key_mod & SDL_KMOD_ALT)
        return Cabe::EKeyMod::ALT;

    return Cabe::EKeyMod::NONE;
}

std::string
GetModName(const SDL_Keymod mod)
{
    std::string name;

#define ADD_MOD(sdl_mod)                                                       \
    if (mod & SDL_KMOD_##sdl_mod) {                                            \
        if (!name.empty())                                                     \
            name += " + ";                                                     \
        name += #sdl_mod;                                                      \
    }

    ADD_MOD(LSHIFT);
    ADD_MOD(RSHIFT);
    ADD_MOD(LEVEL5);
    ADD_MOD(LCTRL);
    ADD_MOD(RCTRL);
    ADD_MOD(LALT);
    ADD_MOD(RALT);
    ADD_MOD(LGUI);
    ADD_MOD(RGUI);
    ADD_MOD(NUM);
    ADD_MOD(CAPS);
    ADD_MOD(MODE);
    ADD_MOD(SCROLL);

#undef ADD_MOD

    return name.empty() ? "NONE" : name;
}