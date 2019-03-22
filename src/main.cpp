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
  std::cout << "Erro logo ao lancar : " << SDL_GetError << std::endl;
  Game* game = &Game :: GetInstance();
  std::cout << "Endereço do game --> " << game << std::endl;
  game->Run();



    
  // SDL_Texture* texture = IMG_LoadTexture(renderer, "resources/ocean.jpg");
  // int textureWidth, textureHeight;
  // SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

  // SDL_Rect sourceRect = {0, 0, textureWidth, textureHeight};
  // SDL_Rect onScreenRect = {0, 0, 1024, 600};
  // SDL_RenderCopyEx(renderer, texture, &sourceRect, &onScreenRect, 0, nullptr, SDL_FLIP_NONE);
  // SDL_RenderPresent(renderer);

  // Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
  // Mix_Music* music = Mix_LoadMUS("resources/Tema_Boss_01.wav");
  // Mix_PlayMusic(music, 1);
  // int i = 0;
  // while(++i < 10000000){
  //   if(SDL_QuitRequested()){
  //     break;
  //   }
  // }

  // Mix_FreeMusic(music);
  // Mix_CloseAudio();
  // SDL_DestroyTexture(texture);
  // SDL_DestroyRenderer(renderer);
  // SDL_DestroyWindow(window);
  // IMG_Quit();
  // SDL_Quit();
  return 0;
}