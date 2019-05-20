#ifndef MUSIC_H
#define MUSIC_H
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include "GameObject.h"

using std::string;

class Music {
  private:
    const static string type;
    Mix_Music* music;
  public:
    Music();
    ~Music();
    Music(string file);
    void Play(int times);
    void Stop(int msToStop);
    void Open(string file);
    bool IsOpen();
    const inline string GetType() const {
      return this->type;
    }
    void NotifyCollision(GameObject& other);
};

#endif