#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"
#include "Component.h"
#include <string>
// Sound é quase a mesma classe de Music, mesmo na implementação.

class Sound : public Component{
private:
    Mix_Chunk* chunk;
    // TODO : e se chamar houver uma LISTA de canais? ...
    
    int channel;
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);

    ~Sound();
    void Play(int times);
    void Stop();
    void Open(std::string file);
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
};

#endif