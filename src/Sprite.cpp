#include "Sprite.h"
#include "Game.h"
#include <cstdio>

static int AuxCodeErr = 0;
#ifndef SDL_ABORT_IF_NZERO
    #define SDL_ABORT_IF_NZERO( x ) \
        AuxCodeErr = x; if (AuxCodeErr) myAbort(AuxCodeErr); else printf("Ok passed.\n");
#endif
#ifndef SDL_ABORT_IF_ZERO
    #define SDL_ABORT_IF_ZERO( x ) \
            SDL_ABORT_IF_NZERO(!(x) )
#endif
static void myAbort(int err) {
    std::cerr << "SDL error : " << SDL_GetError() << "\n";
    abort();
}


Sprite :: Sprite() : texture(nullptr) {
  if(this->texture != nullptr)
    throw "Bananas; null ptr doesn't work on list init constructor";
  // this->texture = nullptr;
}

Sprite :: Sprite(std::string file) {
  this->texture = nullptr;
  this->Open(file);
}

Sprite :: ~Sprite() {
  if (this->texture) {  
    SDL_DestroyTexture(this->texture);
  }
}

// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos.

void Sprite :: Render(int x, int y) {
  Game& game = Game :: GetInstance();
  SDL_Renderer* renderer = game.GetRenderer();
  SDL_Rect dsrect;
  dsrect.x = x;
  dsrect.y = y; 
  dsrect.w = this->clipRect.w;
  dsrect.h = this->clipRect.h;
/* ● SDL_Renderer* renderer: O renderizador de Game.
// Render é um wrapper para SDL_RenderCopy, que recebe quatro
// argumentos. /**/


// ● SDL_Texture* texture: A textura a ser renderizada;
// ● SDL_Rect* srcrect: O retângulo de clipagem. Especifica uma área da
// textura a ser "recortada" e renderizada.
// ● SDL_Rect* dstrect: O retângulo destino. Determina a posição na tela
// em que a textura deve ser renderizada (membros x e y). Se os membros
// w e h diferirem das dimensões do clip, causarão uma mudança na
// escala, contraindo ou expandindo a imagem para se adaptar a esses
// valores.
  printf("Before Sprite.Render.SDL_RenderCopy...\n");
  SDL_ABORT_IF_NZERO(SDL_RenderCopy( Game :: GetInstance().GetRenderer(), this->texture, &this->clipRect, &dsrect ));
  
}

void Sprite :: Open(std::string file) {
  if (this->texture) {  
    SDL_DestroyTexture(this->texture);
  }
  Game& instance = Game::GetInstance();
  const char * path = file.c_str();

// 

// 

  this->texture = IMG_LoadTexture(instance.GetRenderer(), path);
  // Trate o caso de IMG_LoadTexture retornar nullptr.
  std::cout << "Texture ~~>" << this->texture << std::endl;
  if(!this->texture) {
    throw std::runtime_error(SDL_GetError());
  }
  // Com a textura carregada, precisamos descobrir suas dimensões.
  // int SDL_QueryTexture(SDL_Texture* texture, Uint32* format, int* access, int* w, int* h)
  //  O segundo e o terceiro parâmetros podem ser nullptr seguramente. Estamos interessados em w e h.
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->width);
  
  //  sete o clip com as dimensões da imagem
  //  SetClip(x : int, y : int, w : int, h : int) : void
  SetClip( 0, 0, this->height, this->width );

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