#ifndef SPRITE_H
#define SPRITE_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include <string>
#include <cstdio>

#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Timer.h"
using std::string;

class Sprite : public Component {
  private:
    const static string type;
    SDL_Texture* texture;
    int width;
    int height;
    // t6
    int frameWidth;
    int frameHeight;
    SDL_Rect clipRect;
    // t5
    Vec2 scale = Vec2(1,1);
    // t6
    int frameCount = 1;
    int currentFrame = 0;
    double timeElapsed = 0;
    double frameTime = 0;
    double secondsToSelfDestruct = 0.0;
    Timer selfDestructCount;
    // gambs [?]
    double currentDt = 0.0;  // motivo : paara rotacao ser condizendo com o hardware que estah rodando
  public:
    double angleToRotate = 0.0;
    double angleCurrent = 0.0;
    Sprite() {} //gambs; por conta do Sprite de State
    Sprite(GameObject&);
    Sprite(GameObject&, string file);
    // t6
    Sprite(GameObject&, string file, int frameCount,
          double frameTime, double secondsToSelfDestruct = 0.0);
    
    virtual ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);    
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
    void Rotate(double angle = 0.0);
    void RotateDt(double externalDt, double angle = 0.0);
    void NotifyCollision(GameObject& other);

};

#endif