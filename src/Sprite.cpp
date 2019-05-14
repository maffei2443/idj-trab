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
  cout << "FrameCount: " << this->frameCount << endl;
  cout << "frameTime: " << this->frameTime << endl;
  this->texture = nullptr;
  this->Open(file);
  this->associated.AddComponent( this );  // adicionar a si mesmo no vetor do associated que o contem
}

Sprite::Sprite(GameObject& associated, string file, int frameCount, double frameTime) : 
  Component(associated), frameCount(frameCount), frameTime(currentFrame) {
  cout << "Sprite nao-padrao! " << endl;
  cout << "[NT]FrameCount: " << this->frameCount << endl;
  cout << "[NT]frameTime: " << this->frameTime << endl;

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
  SDL_ClearError();
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
}

void Sprite::Update(double dt) {
  
  this->angleCurrent += this->angleToRotate * dt;
  // t6
  //   Update deve acumular os dts em timeElapsed. Se timeElapsed for maior
  // que o tempo de um frame, passamos para o frame seguinte, setando o clip.
  this->timeElapsed += dt;
  
  if (this->timeElapsed > this->frameTime) {
    // TODO: passar para o proximo frame
    this->currentFrame++;
    this->currentFrame %= this->frameCount;
    if(this->associated.GetComponent("Bullet"))
      cout << "Bullet Frame : " << this->currentFrame << endl;
    // Se proximo frame eh o ultimo, volta ao primeiro
  }
}


void Sprite::Render() {
  this->Render(this->associated.box.x, this->associated.box.y);  
}

void Sprite::Open(string file) {
  // if (this->texture) {  
  //   SDL_DestroyTexture(this->texture);
  // }
  SDL_ClearError();
  this->texture = Resources::GetImage( file );
  SDL_ABORT_IF_ZERO(this->texture);
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
  this->frameWidth = this->width / this->frameCount;
  this->frameHeight = this->height / this->frameCount;
  // cout << "[Sprite.cpp] this->width " << this->width << endl;
  cout << "[Sprite.cpp] this->frameWidth " << this->frameWidth << endl;
  // cout << "[Sprite.cpp] this->height " << this->height << endl;
  cout << "[Sprite.cpp] this->frameHeight " << this->frameHeight << endl;
  // this->SetClip( 
  //   this->currentFrame * this->frameWidth,
  //   this->currentFrame * this->,frameHeight,
  //   this->frameWidth,
  //   this->frameHeight
  // );
  // POSSIVEL BUG : se quiser-se iniciar no último frame,
  // vai dar problema...
  SetClip( currentFrame * this->frameWidth,
           0,
           this->frameWidth/*   */,
           this->height/*    */);
  
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
  this->associated.box.SetCenter(this->associated.box.GetCenter());
}

void Sprite::SetScale(Vec2 scale) {
  this->SetScale(scale.x, scale.y);
}

// t6
// t6
void Sprite::SetFrame(int frameTime) {

}

void Sprite::SetFrameCount(int frameCount) {

}

void Sprite::SetFrameTime(double frameTime) {

}
