#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <cstdio>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
using std::string;
// I am a component!

class Sprite : public Component {
  // A classe Sprite encapsula o carregamento e uso de SDL_Textures,
  // da SDL que contém uma imagem carregada do disco pronta para 
  private:
    const static string type;
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
  public:
    Sprite() {
      //////printf("CONTRUCTOR SPRITE ROUBADO\n");
    } //gambs; por conta do Sprite de State
    Sprite(GameObject&);
    Sprite(GameObject&, string file);
    virtual ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int, int);
    // void Render(int x, int y);
    
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    // herda de Component
    void Update(double dt);
    bool Is(string type);
    void Render();
    const inline string GetType() const {
        return this->type;
    }
    // t5
    bool started = false;
    void Start();    
};

#endif