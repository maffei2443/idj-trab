#include "InputManager.h"
#define INCLUDE_SDL
#include "SDL_include.h"


#include <cstdio>
#include <iostream>
#include "Macros.h"
void InputManager::Update() {

	SDL_Event event;
  // Primeiro, obter as coordenadas atuais do mouse (SDL_GetMouseState
	
	// Segundo resetar a flag de quit. [? NAO FAZ SENTIDO; PODE MUDAR 
  // ENTRE ESSA LINHA E A PRÓXIMA]
  // this->quitRequested = false;
  /* para todo evento, seja botão ou tecla, deve
  ocorrer o registro do valor do contador de updates do frame atual para aquela
  tecla. [?] */
  int keyVal;
  int pressedButton;
  // POR QUE WHILE E NAO IF?
  bool flag = true;  // Controla incremento após o while
  while (SDL_PollEvent(&event)) {    
    flag = false;
    this->updateCounter++;
    // printf("inside while counter  ++\n");
    keyVal = event.key.keysym.sym;
    pressedButton = event.button.button;
    switch (event.type) {
      case SDL_KEYDOWN:
        // printf("KEY PRESSED : %d\n", keyVal);
        if (!event.key.repeat) {
          this->keyState[keyVal] = true;
          this->keyUpdate[keyVal] = this->updateCounter;          
          if(keyVal == ESCAPE_KEY) {
            this->quitRequested = true;
          }
        }
        // printf("KEY_DOWN %d\n", keyVal);
        // printf("KeyPress(keyVal) %d\n", KeyPress(keyVal));
        // printf("%d\n",keyVal);//abort();
        break;
      case SDL_KEYUP:  // Uma tecla foi solta
        this->keyState[keyVal] = false;
        this->keyUpdate[keyVal] = this->updateCounter;
        // printf("KEY_UP %d\n", keyVal);
        break;
      case SDL_QUIT: // Clique no X, Alt+F4, etc.
        printf("QUITOU %d\n", keyVal);
        printf("ESC %d\n", SDL_QUIT);
        this->quitRequested = true;break;    // QUIT deve ser tratado simplesmente setando a flag quitRequested.
      case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&this->mouseX, &this->mouseY);
        this->mouseState[pressedButton] = true;
        this->mouseUpdate[pressedButton] = this->updateCounter;
        // printf("MOUSE_BUTTON_DOWN %d\n", pressedButton);
        break;
      case SDL_MOUSEBUTTONUP: // Botão do mouse foi solto
        SDL_GetMouseState(&this->mouseX, &this->mouseY);
        this->mouseState[pressedButton] = false;
        this->mouseUpdate[pressedButton] = this->updateCounter;
        // printf("MOUSE_BUTTON_UP %d\n", pressedButton);
        break;

    }
  }
  if (flag) {
    this->updateCounter++;
  }
}

// POSSIVEL BUG
bool InputManager::KeyPress(int key) {
  // printf("KeyPress %d? \n", key);
  int state = this->keyState[key], counter = this->updateCounter;
  if(state == true and (counter-1 == this->keyUpdate[key] || counter == this->keyUpdate[key])) {
      return true;
  }
  return false;
}

// POSSIVEL BUG
bool InputManager::KeyRelease(int key) {
  if(this->keyUpdate.count(key)) {
    if (this->keyUpdate[key] == this->updateCounter)
      return !this->keyState[key];// == false;
  }
  return false;
}

// Is___Down retorna se o botão/tecla
// está pressionado, independente de quando isso ocorreu.

// Is___Down retorna se o botão/tecla
// está pressionado, independente desde quando

bool InputManager::IsKeyDown(int key) {
  if(this->keyState.count(key)) {
    return this->keyState[key];
  }
  return false;
}

// POSSIVEL BUG BUG

bool InputManager::MousePress(int button) {
  if(this->mouseState[button]) {  //  estah pressionado
    if (this->mouseUpdate[button] == this->updateCounter)  // atualizado ultimo frame
      return true;
  }
  return false;
}

// POSSIVEL BUG BUG
bool InputManager::MouseRelease(int button) {
  if(!this->mouseState[button]) {  // nao estah pressionado
    if (this->mouseUpdate[button] == this->updateCounter)  // atualizado ultimo frame
      return true;
  }
  return false;
}

// POSIVEL BUG
bool InputManager::IsMouseDown(int button) {
  if(this->keyState.count(button)) {
    return this->keyState[button];
  }
  return false;
}

int InputManager::GetMouseX() {
  return this->mouseX;
}

int InputManager::GetMouseY() {
  return this->mouseY;
}

bool InputManager::QuitRequested() {
  return this->quitRequested;
}

InputManager& InputManager::GetInstance() {
    static InputManager mayerSingleton;
    return mayerSingleton;
}

// Ok, inicializa variáveis de InputManager.
InputManager::InputManager () : quitRequested(false), updateCounter(0) {
  SDL_GetMouseState(&mouseX, &mouseY);
/* O construtor deve inicializar os arrays de estado e update do mouse. Se
você estiver usando vetores para as teclas, faça o mesmo para eles. Já as
tabelas de hash não precisam (nem devem) ser inicializadas. Lembre-se
também das outras variáveis da classe (updateCounter, quitRequested e
mouse) */
  // keyUpdate e keyState não precisam de inicialização pois são HASH
  this->mouseState = std::vector<bool>(6, false);
  this->mouseUpdate = std::vector<int>(6, 0);
}

InputManager::~InputManager () {

}

