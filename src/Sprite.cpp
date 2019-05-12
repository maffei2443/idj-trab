#include <cstdio>

#include "Macros.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
const string Sprite::type("Sprite");
#include <string>
using std::string;
#include "Util.h" // IsDoubleZero
void Sprite::ApplyScale() {
  this->associated.box.w *= this->scale.x;
  this->associated.box.h *= this->scale.y;
}

Sprite::Sprite(GameObject& associated) : Component(associated) {
  this->texture = nullptr;
  this->associated.AddComponent( this );  // adicionar a si mesmo no vetor do associated que o contem
}

Sprite::Sprite(GameObject& associated, string file) : Component(associated) {
  this->texture = nullptr;
  this->Open(file);
  this->associated.AddComponent( this );  // adicionar a si mesmo no vetor do associated que o contem
}

Sprite::~Sprite() {
}

// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos.

void Sprite::Render(int x, int y) { 
  SDL_Rect dsrect;
  dsrect.x = x;
  dsrect.y = y; 
  dsrect.w = this->clipRect.w * this->scale.x;
  dsrect.h = this->clipRect.h * this->scale.y;
  /* Para o zoom, você deve ajustar para a escala as dimensões do retângulo
de destino (quarto argumento da SDL_RenderCopy). O tamanho do Sprite
será ajustado automaticamente para ocupar o novo retângulo. */


/* ● SDL_Renderer* renderer: O renderizador de Game.
// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos. /**/

  SDL_ClearError();
  // SDL_ABORT_IF_NZERO(
  //   SDL_RenderCopy( 
  //     Game::GetInstance().GetRenderer(), 
  //     this->texture, 
  //     &this->clipRect, 
  //     &dsrect 
  //   )
  // );
  /* Para a rotação, vamos substituir a SDL_RenderCopy pela
  SDL_RenderCopyEx. Ela recebe sete argumentos, sendo os quatro primeiros
os mesmos da RenderCopy.*/
/* Os três outros são:
● angle : double - Ângulo de rotação no sentido horário em graus.
● center : SDL_Point* - Determina o eixo em torno da qual a rotação
ocorre. Se passarmos nullptr, a rotação ocorre em torno do centro do
retângulo de destino, que é o que queremos.
● flip : SDL_RendererFlip - Inverte a imagem verticalmente
(SDL_FLIP_VERTICAL), horizontalmente (SDL_FLIP_HORIZONTAL),
ambos (bitwise or), ou não inverte (SDL_FLIP_NONE). Você pode
implementar suporte à inversão de Sprites se quiser, mas por enquanto,
use SDL_FLIP_NONE. */
  SDL_ABORT_IF_NZERO(
    SDL_RenderCopyEx( 
      Game::GetInstance().GetRenderer(), 
      this->texture, 
      &this->clipRect, 
      &dsrect,
      this->angleCurrent,
      nullptr,
      SDL_FLIP_NONE
    )
  );
  this->angleCurrent += this->angleToRotate;
  this->angleCurrent -= (360 < fabs(this->angleCurrent) ? 360 : 0);
}


void Sprite::Render() {
  int x = this->associated.box.x + Camera::speed.x;
  int y = this->associated.box.y + Camera::speed.y;
  this->Render(x, y);  
}

void Sprite::Open(string file) {
  // if (this->texture) {  
  //   SDL_DestroyTexture(this->texture);
  // }
  SDL_ClearError();
  // this->texture = IMG_LoadTexture(instance.GetRenderer(), path);
  this->texture = Resources::GetImage( file );
  // Trate o caso de IMG_LoadTexture retornar nullptr.
  SDL_ABORT_IF_ZERO(this->texture);
  // Com a textura carregada, precisamos descobrir suas dimensões.
  // int SDL_QueryTexture(SDL_Texture* texture, Uint32* format, int* access, int* w, int* h)
  //  O segundo e o terceiro parâmetros podem ser nullptr seguramente. Estamos interessados em w e h.
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
  
  //  sete o clip com as dimensões da imagem
  //  SetClip(x : int, y : int, w : int, h : int) : void
  SetClip( 0, 0, this->width, this->height );

}

void Sprite::SetClip(int x, int y, int w, int h) {
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.w = w * this->scale.x;
  this->clipRect.h = h * this->scale.y;
}

int Sprite::GetWidth() {
  return this->width*this->scale.x;
}

int Sprite::GetHeight() {
  return this->height*this->scale.y;
  
}

bool Sprite::IsOpen() {
  return !!this->texture; 
}

void Sprite::Update(double dt) {
  (void)dt;
  // printf("\tSprite UPDATE OK\n");
}

bool Sprite::Is(string type) {
  return type == "Sprite";
}

void Sprite::Start() {
  this->started = true;
}
/* A função SetScale é apenas um método Set para a escala. Mantenha a
escala em dado eixo se o valor passado para ela for 0. */
void Sprite::SetScale(double scaleX, double scaleY) {
  if(IsDoubleZero(scaleX))  scaleX = 1;
  if(IsDoubleZero(scaleY))  scaleY = 1;
  this->scale = Vec2(scaleX, scaleY);
  /* Não se esqueça de atualizar a box do GameObject associated. Para
facilitar no futuro, mova a box dele de forma a manter o centro no mesmo
lugar de antes da mudança de escala. */
  this->associated.box.w *= scaleX;
  this->associated.box.h *= scaleY;
  this->associated.box.SetCenter(this->associated.box.center);
}

void Sprite::SetScale(Vec2 scale) {
  this->SetScale(scale.x, scale.y);
}