#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
#include <map>
#include <vector>
using std::map;
using std::vector;
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT



class InputManager {
  private:
    vector<bool> mouseState;
    vector <int> mouseUpdate;
    vector <int> mouseRepeat;
    map<int, bool> keyState;
    map<int, int> keyUpdate;
    map<int, int> keyRepeat;
    bool quitRequested;

    int updateCounter;
    int mouseX;
    int mouseY;
    static const string type;
  public:
    void Update();
/* ___Press e ___Release estão interessadas no pressionamento
ocorrido naquele frame */
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    
    int GetMouseX();
    int GetMouseY();
    bool QuitRequested();
    static InputManager& GetInstance();
    InputManager ();
    ~InputManager ();
    const inline string GetType() const {
      return this->type;
    }
};

#endif