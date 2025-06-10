#include "File.h"

#include <SDL3/SDL_Log.h>
#include <SDL3/SDL_iostream.h>

File::File(const char* file_path) : m_Path(file_path) {
    // TODO : Do lazy loading

    size_t size;
    char* data = static_cast<char*>(SDL_LoadFile(file_path, &size));

    if (!data) {
        SDL_Log("Error : Could'nt load file");
        SDL_Log("Reason : %s", SDL_GetError());
        // TODO("Exit Gracefully")
        return;
    }

    m_Text.Populate(data);
}