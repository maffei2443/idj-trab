#include <cstdio>
#include <string>

#include "Macros.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
  this->texture = nullptr;

  // this->texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated) {
  this->texture = nullptr;
  this->Open(file);
  this->associated.AddComponent( this );  // adicionar a si mesmo no vetor do associated que o contem
}

Sprite::~Sprite() {
  // Agora isso é papel da Resources
  // if (this->texture) {
  //   // //////printf(">>>>>>>>>>>>> DESTROYER <<<<<<<<<<<<<<\n");
  //   SDL_DestroyTexture(this->texture);
  // }
}

// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos.

void Sprite::Render(int x, int y) { 
  SDL_Rect dsrect;
  dsrect.x = x;
  dsrect.y = y; 
  dsrect.w = this->clipRect.w;
  dsrect.h = this->clipRect.h;
/* ● SDL_Renderer* renderer: O renderizador de Game.
// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos. /**/

  SDL_ABORT_IF_NZERO(SDL_RenderCopy( Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &dsrect ));
  SDL_ClearError();

}


void Sprite::Render() {
  int x = this->associated.box.x - Camera::pos.x;
  int y = this->associated.box.y - Camera::pos.y;  

  this->Render(x, y);
}

void Sprite::Open(std::string file) {
  // if (this->texture) {  
  //   SDL_DestroyTexture(this->texture);
  // }
  // //////std::cout << "Error before load_texture? ~~>" << SDL_GetError() << std::endl;
  SDL_ClearError();
  // this->texture = IMG_LoadTexture(instance.GetRenderer(), path);
  this->texture = Resources::GetImage( file );
  // Trate o caso de IMG_LoadTexture retornar nullptr.
  SDL_ABORT_IF_ZERO(this->texture);
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
  SetClip( 0, 0, this->width, this->height );

}

void Sprite::SetClip(int x, int y, int w, int h) {
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.w = w;
  this->clipRect.h = h;
}

int Sprite::GetWidth() {
  return this->width;
}

int Sprite::GetHeight() {
  return this->height;
  
}

bool Sprite::IsOpen() {
  return !!this->texture; 
}

void Sprite::Update(float dt) {
  (void)dt;
}

bool Sprite::Is(std::string type) {
  return type == "Sprite";
}
