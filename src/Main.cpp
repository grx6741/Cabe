#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

static struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *render_target;
} s_EditorState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    // TODO("Parse command line arguments and set up app state here");
    (void)appstate;
    (void)argc;
    (void)argv;

    SDL_SetAppMetadata("Cabe", "0.1", "https://github.com/grx6741/Cabe");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
            "examples/CATEGORY/NAME", 640, 480, SDL_WINDOW_RESIZABLE,
            &s_EditorState.window, &s_EditorState.renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderVSync(s_EditorState.renderer, 1);

    s_EditorState.render_target =
        SDL_CreateTexture(s_EditorState.renderer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET, 100, 100);

    // setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // theme
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(s_EditorState.window,
                                      s_EditorState.renderer);
    ImGui_ImplSDLRenderer3_Init(s_EditorState.renderer);

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            // Handle quit event
            return SDL_APP_SUCCESS;
            break;

        case SDL_EVENT_KEY_DOWN:
#ifdef DEBUG
            if (event->key.key == SDLK_ESCAPE) {
                return SDL_APP_SUCCESS;
            }
#endif
            break;
    }

    ImGui_ImplSDL3_ProcessEvent(event);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    SDL_Texture *old_render_target =
        SDL_GetRenderTarget(s_EditorState.renderer);
    SDL_SetRenderTarget(s_EditorState.renderer, s_EditorState.render_target);

    const double now = ((double)SDL_GetTicks()) / 1000.0;
    const float red = (float)(0.5 + 0.5 * SDL_sin(now));
    const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(s_EditorState.renderer, red, green, blue,
                                SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(s_EditorState.renderer);

    SDL_SetRenderTarget(s_EditorState.renderer, old_render_target);

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    ImGui::Begin("Main.cpp");
    ImGui::Image((ImTextureID)(intptr_t)s_EditorState.render_target,
                 ImVec2(200, 200));
    ImGui::End();

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),
                                          s_EditorState.renderer);

    SDL_RenderPresent(s_EditorState.renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyTexture(s_EditorState.render_target);
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}