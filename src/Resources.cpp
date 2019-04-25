#include <string>
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources :: GetImage(std::string file) {
  Game& instance = Game::GetInstance();
  // //////std::cout << "Error before load_texture? ~~>" << SDL_GetError() << std::endl;
  SDL_ClearError();
  auto it = imageTable.find(file);
  SDL_Texture* texture;
  if( it == Resources::imageTable.end() ) {
    texture = IMG_LoadTexture(instance.GetRenderer(), file.c_str());
  // Trate o caso de IMG_LoadTexture retornar nullptr.    
    SDL_ABORT_IF_ZERO(texture);
    Resources::imageTable[file] = texture;
  }
  else {
    texture = it->second;
  }
  return texture;
}

void Resources :: ClearImages() {
  Resources::imageTable.clear();
}

Mix_Music* Resources :: GetMusic(std::string file) {
  Mix_Music* music;
  auto it = Resources::musicTable.find(file);
  if( it == Resources::musicTable.end() ) {
    music = Mix_LoadMUS(file.c_str());
    SDL_ABORT_IF_ZERO(music);
    Resources::musicTable[file] = music;
  }
  else {
    music = it->second;
  }
  return music;
}

void Resources :: ClearMusics() {
  Resources::musicTable.clear();
}

Mix_Chunk* Resources :: GetSound(std::string file) {
  Mix_Chunk* sound;
  auto it = Resources::soundTable.find(file);
  if( it == Resources::soundTable.end() ) {
    sound = Mix_LoadWAV(file.c_str());
    // Trate o caso de IMG_LoadTexture retornar nullptr.    
    SDL_ABORT_IF_ZERO(sound);
    Resources::soundTable[file] = sound;
  }
  else {
    sound = it->second;
  }
  return sound;
}

void Resources :: ClearSounds() {
  Resources::soundTable.clear();
}

