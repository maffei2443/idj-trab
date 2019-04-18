#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Game.h"
// #include <iostream>
// #include "SDL.h"
// #include "SDL_image.h"
// #include "SDL_mixer.h"


// void TestAllocatedTexture() {
//   SDL_Texture* texture = IMG_LoadTexture(instance->GetRenderer(), path);
//  if(!texture) 
// }

int main(int argc, char** argv)
{
  (void)argc; (void)argv;
  // //////std::cout << "Erro logo ao lancar : " << SDL_GetError() << std::endl;
  Game* game = &Game::GetInstance();
  //////std::cout << "Endereço do game --> " << game << std::endl;
  game->Run();
  return 0;
}