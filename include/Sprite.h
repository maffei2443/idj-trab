#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
class Sprite {
  // A classe Sprite encapsula o carregamento e uso de SDL_Textures,
  // da SDL que contém uma imagem carregada do disco pronta para 
  private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
  public:
    Sprite();
    Sprite(std::string file);
    ~Sprite();
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    
    int GetWidth();
    int GetHeight();
    bool IsOpen();
};

#endif