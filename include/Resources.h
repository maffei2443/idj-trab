#ifndef RESOURCES_H
#define RESOURCES_H
#include <string>
#include <unordered_map>
#define INCLUDE_SDL
#include "SDL_include.h"

class Resources {
private:
    /* O membro imageTable é associado uma string (o
    caminho de um arquivo) a um ponteiro de textura. */
    std::unordered_map<std::string, SDL_Texture*> imageTable;
    std::unordered_map<std::string, Mix_Music*> musicTable;
    std::unordered_map<std::string, Mix_Chunk*> soundTable;
    
public:
    static SDL_Texture* GetImage(std::string);
    static void ClearImages();
    
    static Mix_Music* GetMusic(std::string);
    static void ClearMusics();

    static Mix_Chunk* GetSound(std::string);
    static void ClearSounds();
};

#endif