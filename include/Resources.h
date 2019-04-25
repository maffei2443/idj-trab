#ifndef RESOURCES_H
#define RESOURCES_H
#include <string>
#include <unordered_map>

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"

class Resources {
private:
    /* O membro imageTable é associado uma string (o
    caminho de um arquivo) a um ponteiro de textura. */
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
    
public:
    static SDL_Texture* GetImage(std::string);
    static void ClearImages();
    
    static Mix_Music* GetMusic(std::string);
    static void ClearMusics();

    static Mix_Chunk* GetSound(std::string);
    static void ClearSounds();
};

#endif