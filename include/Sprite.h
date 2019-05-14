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
    // t5
    Vec2 scale = Vec2(1,1);
    // t6
    int frameCount;
    int currentFrame;
    double timeElapsed = 0;
    double frameTime = 0;
  public:
    double angleToRotate = 0.0;
    double angleCurrent = 0.0;
    Sprite() {
      //////printf("CONTRUCTOR SPRITE ROUBADO\n");
    } //gambs; por conta do Sprite de State
    Sprite(GameObject&);
    Sprite(GameObject&, string file);
    // t6
    Sprite(GameObject&, string file, int frameCount=1, double frameTime);
    
    virtual ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    // void Render(int, int);
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
    void SetScale(double scaleX=0, double scaleY=0);
    void SetScale(Vec2 scale);
    Vec2 GetScale(double, double);
    void Render(int x, int y);
    void ApplyScale();

    // t6
    void SetFrame(int);
    void SetFrameCount(int);
    void SetFrameTime(double);
    
};

#endif