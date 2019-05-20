#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"
#include "Component.h"
#include <string>
// Sound é quase a mesma classe de Music, mesmo na implementação.
using std::string;

class Sound : public Component{
private:
    const string type = string("Sound");
    Mix_Chunk* chunk;
    // TODO : e se chamar houver uma LISTA de canais? ...
    
    int channel;

public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, string file);

    virtual ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(string file);
    bool IsOpen();

    // Herdou
    void Update(double dt);
    void Render();
    bool Is(string type);

    const inline string GetType() const {
        return this->type;
    }
    // t5
    bool started = false;
    void Start();
    void NotifyCollision(GameObject& other);
};

#endif