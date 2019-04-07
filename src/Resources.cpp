#include "Resources.h"
#include "Game.h"
#include <string>
#define INCLUDE_SDL
#include "SDL_include.h"

static SDL_Texture* Resources :: GetImage(std::string file) {
  Game& instance = Game::GetInstance();
  const char * path = file.c_str();
  // std::cout << "Error before load_texture? ~~>" << SDL_GetError() << std::endl;
  SDL_ClearError();
  auto it = Resources::imageTable.find(file);
  SDL_Texture* texture;
  if( it == Resources::imageTable.end() ) {
    texture = IMG_LoadTexture(instance.GetRenderer(), file);
  // Trate o caso de IMG_LoadTexture retornar nullptr.    
    SDL_ABORT_IF_ZERO(texture);
    Resources::imageTable[file] = texture;
  }
  else
    texture = *it;
  return texture;
}

static void Resources :: ClearImages() {
  for(auto it = Resources::imageTable.begin(); it != Resources::imageTable.begin(); it++)
    delete it->second;
}

static SDL_Music* Resources :: GetMusic(std::string file) {
  Game& instance = Game::GetInstance();
  const char * path = file.c_str();
  // std::cout << "Error before load_texture? ~~>" << SDL_GetError() << std::endl;
  SDL_ClearError();

  Mix_MUsic* music;
  auto it = Resources::musicTable.find(file);

  if( it == Resources::musicTable.end() ) {
    music = Mix_LoadMUS(instance.GetRenderer(), file);
  // Trate o caso de IMG_LoadTexture retornar nullptr.    
    SDL_ABORT_IF_ZERO(music);
    Resources::musicTable[file] = music;
  }
  else
    texture = *it;
  return texture;

}

static void Resources :: ClearMusics() {
  for(auto it = Resources::musicTable.begin(); it != Resources::musicTable.begin(); it++)
    delete it->second;
}

static SDL_Texture* Resources :: GetSound() {

}

static void Resources :: ClearSounds() {
  for(auto it = Resources::soundTable.begin(); it != Resources::soundTable.begin(); it++)
    delete it->second;

}

