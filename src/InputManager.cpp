#include "InputManager.h"
#define INCLUDE_SDL
#include "SDL_include.h"

#include "Face.h"
#include <cstdio>
#include <iostream>
#include "Macros.h"
void InputManager::Update() {
  /* Update faz o processamento de eventos, de forma similar a como
  fizemos em Game::Input. Fazemos uso da função SDL_PollEvent, uma função
  que recebe um ponteiro para uma variável do tipo SDL_Event. Se houver um
  evento ainda a ser processado, ela retorna true e o grava na variável de
  evento. Se não, retorna false */
	/* TODO : deletar essa função.
	Agora quem lida com isso é o InputManager */
	SDL_Event event;
	// Obtenha as coordenadas do mouse
  // Primeiro, obter as coordenadas atuais do mouse (SDL_GetMouseState
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
	// Segundo resetar a flag de quit. [? NAO FAZ SENTIDO; PODE MUDAR 
  // ENTRE ESSA LINHA E A PRÓXIMA]

  /* para todo evento, seja botão ou tecla, deve
  ocorrer o registro do valor do contador de updates do frame atual para aquela
  tecla. */
  int keyVal;
  int pressedButton;
  while (SDL_PollEvent(&event)) {
    keyVal = event.key.keysym.sym;
    pressedButton = event.button.button;
    switch (event.type) {
      case SDL_KEYDOWN:
        // caso de ESC
        this->quitRequested = keyVal == ASCII_ESC;
        this->keyState[keyVal] = true;
        this->keyUpdate[keyVal] = this->updateCounter;
        printf("KEY_DOWN %d\n", keyVal);break;
      case SDL_KEYUP:  // Uma tecla foi solta
        this->keyState[keyVal] = false;
        this->keyUpdate[keyVal] = this->updateCounter;
        printf("KEY_UP %d\n", keyVal);break;
      case SDL_QUIT: // Clique no X, Alt+F4, etc.
        printf("QUITOU %d\n", keyVal);
        printf("ESC %d\n", SDL_QUIT);
        this->quitRequested = true;break;    // QUIT deve ser tratado simplesmente setando a flag quitRequested.
      case SDL_MOUSEBUTTONDOWN:
        this->mouseState[event.button.button] = true;
        this->mouseUpdate[event.button.button] = this->updateCounter;
        printf("MOUSE_BUTTON_DOWN %d\n", event.button.button);break;
      case SDL_MOUSEBUTTONUP: // Botão do mouse foi solto
        this->mouseState[event.button.button] = false;
        this->mouseUpdate[event.button.button] = this->updateCounter;
        printf("MOUSE_BUTTON_DOWN %d\n", event.button.button);break;
    }
    this->updateCounter++;
  }
  // printf("--------------\n");
  // abort();
}

// POSSIVEL BUG
bool InputManager::KeyPress(int key) {
  if(this->keyUpdate.count(key)) {
    if (this->keyUpdate[key] == this->updateCounter)
      return this->keyState[key];// == true;
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
// está pressionado, independente de quando isso ocorreu
bool InputManager::IsKeyDown(int key) {
  if(this->keyState.count(key)) {
    return this->keyState[key];
  }
  return false;
}

// POSSIVEL BUG BUG
bool InputManager::MousePress(int button) {
  return this->mouseState[button];
}
// POSSIVEL BUG BUG
bool InputManager::MouseRelease(int button) {
  return this->mouseUpdate[button];
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
InputManager::InputManager () :updateCounter(0), quitRequested(false) {
  SDL_GetMouseState(&mouseX, &mouseY);
/* O construtor deve inicializar os arrays de estado e update do mouse. Se
você estiver usando vetores para as teclas, faça o mesmo para eles. Já as
tabelas de hash não precisam (nem devem) ser inicializadas. Lembre-se
também das outras variáveis da classe (updateCounter, quitRequested e
mouse) */
  // keyUpdate e keyState não precisam de inicialização pois são HASH
  this->mouseState = std::vector<bool>(6, false);
  this->mouseUpdate = std::vector<bool>(6, false);
}

InputManager::~InputManager () {

}

