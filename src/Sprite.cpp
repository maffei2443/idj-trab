#include "Sprite.h"
#include "GameObject.h"
#include "Game.h"
#include <cstdio>
#include <string>

#include "Macros.h"



Sprite :: Sprite(GameObject& associated) : Component(associated) {
  this->texture = nullptr;
  if(this->texture != nullptr)
    LOG("Bananas; null ptr doesn't work on list init constructor\n");
  // this->texture = nullptr;
}

Sprite :: Sprite(GameObject& associated, std::string file) : Component(associated) {
  this->texture = nullptr;
  this->Open(file);
  this->associated.AddComponent( this );  // adicionar a si mesmo no vetor do associated que o contem
}

Sprite :: ~Sprite() {
  if (this->texture) {
    // printf(">>>>>>>>>>>>> DESTROYER <<<<<<<<<<<<<<\n");
    SDL_DestroyTexture(this->texture);
  }
}

// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos.

void Sprite :: Render() {
  // printf("Render sprite of type |---> ...\n");
  
  int x = this->associated.box.x;
  int y = this->associated.box.y;
  Game& game = Game :: GetInstance();
  SDL_Renderer* renderer = game.GetRenderer();
  SDL_Rect dsrect;
  dsrect.x = this->associated.box.x;
  dsrect.y = this->associated.box.y; 
  dsrect.w = this->clipRect.w;
  dsrect.h = this->clipRect.h;
/* ● SDL_Renderer* renderer: O renderizador de Game.
// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos. /**/

  // printf("Before Sprite.Render.SDL_RenderCopy...\n");
  // printf("ERROS :%s\n", SDL_GetError());
  SDL_ABORT_IF_NZERO(SDL_RenderCopy( Game :: GetInstance().GetRenderer(), this->texture, &this->clipRect, &dsrect ));
  SDL_ClearError();
  // printf("Should be empty ---> %s\n", SDL_GetError());
  SDL_RenderCopy( Game :: GetInstance().GetRenderer(), this->texture, &this->clipRect, &dsrect );
  // auto a = this->clipRect;
  // SDL_RenderCopy( Game :: GetInstance().GetRenderer(), this->texture, &this->clipRect, &dsrect );
  
}

void Sprite :: Open(std::string file) {
  if (this->texture) {  
    SDL_DestroyTexture(this->texture);
  }
  Game& instance = Game::GetInstance();
  const char * path = file.c_str();
  // std::cout << "Error before load_texture? ~~>" << SDL_GetError() << std::endl;
  SDL_ClearError();
  this->texture = IMG_LoadTexture(instance.GetRenderer(), path);
  // Trate o caso de IMG_LoadTexture retornar nullptr.
  
  // std::cout << "Texture ~~>" << this->texture << std::endl;
  // std::cout << "Error after loadd_texture? ~~>" << SDL_GetError() << std::endl;
  
  // if(!this->texture) {
  //   LOG(std::runtime_error(SDL_GetError());
  // }

  // Com a textura carregada, precisamos descobrir suas dimensões.
  // int SDL_QueryTexture(SDL_Texture* texture, Uint32* format, int* access, int* w, int* h)
  //  O segundo e o terceiro parâmetros podem ser nullptr seguramente. Estamos interessados em w e h.
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
  
  //  sete o clip com as dimensões da imagem
  //  SetClip(x : int, y : int, w : int, h : int) : void
  SetClip( 0, 0, this->width, this->height );

}

void Sprite :: SetClip(int x, int y, int w, int h) {
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.w = w;
  this->clipRect.h = h;
}

int Sprite :: GetWidth() {
  return this->width;
}

int Sprite :: GetHeight() {
  return this->height;
  
}

bool Sprite :: IsOpen() {
  return !!this->texture; 
}

void Sprite :: Update(float dt) {

}

bool Sprite :: Is(std :: string type) {
  return type == "Sprite";
}
