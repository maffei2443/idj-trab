#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
#include <map>
#include <vector>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT


/* Ele [] é um singleton que lê a pilha de eventos sempre que 
seu método Update é chamado (no início de cada frame).
 */
class InputManager {
  public:
    void Update();
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
  private:
  /* Cada mudança no estado de uma tecla ou botão do mouse é registrada
no array e na tabela contidos na classe. Como a SDL indexa botões do mouse
de 1 a 5, não é necessário nada além de um array simples para fazermos
acesso direto. */
    std::vector<bool> mouseState;
    std::vector <bool> mouseUpdate;
    /* No entanto, para as teclas, os valores de SDL_Keycodes (a enum da SDL
que se refere às teclas) estão um pouco mais espalhadas. Teclas cujos valores
tem um caracter correspondente tem keycodes no range 0x0 até 0x7F, igual
ao valor na tabela ASCII. */
    std::map<int, bool> keyState;
    std::map<int, int> keyUpdate;
    /* De verdade, apenas keyState e mouseStateguardam estado - true se
    o botão está pressionado, false caso contrário */
    bool quitRequested;

    int updateCounter;
    int mouseX;
    int mouseY;

};

#endif