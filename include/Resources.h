#ifndef RESOURCES_H
#define RESOURCES_H
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <string>

class Resources {
private:
    /* O membro imageTable é associado uma string (o
    caminho de um arquivo) a um ponteiro de textura. */
    static unordered_map<string, SDL_Texture*> imageTable;
    static unordered_map<string, Mix_Music*> musicTable;
    static unordered_map<string, Mix_Chunk*> soundTable;
    
public:
    static SDL_Texture* GetImage(string);
    static void ClearImages();
    
    static Mix_Music* GetMusic(string);
    static void ClearMusics();

    static Mix_Chunk* GetSound(string);
    static void ClearSounds();
};

#endif