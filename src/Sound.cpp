#include "Sound.h"
#include "GameObject.h"
#include <exception>
#include <iostream>
#include "Macros.h"


Sound :: Sound(GameObject& associated) : 
    Component(associated),  // chamma construtor de Component, passando associated
    chunk(nullptr) {
}
Sound :: Sound(GameObject& associated,
                std::string file) : Component(associated) {
    this->Open(file);
}
// Se chunk for diferente de nullptr, chame Halt e 
// depois desaloque o som usando o Mix_FreeChunk.
Sound :: ~Sound() {
    /// Se chunk for diferente de nullptr, chame Halt e depois desaloque o
    /// som usando o Mix_FreeChunk.
    if (!this->chunk)
        return;
    Mix_HaltChannel(this->channel);    // Para todas as músicas
    // void Mix_FreeChunk(Mix_Chunk* chunk)
    Mix_FreeChunk(this->chunk);
}
void Sound :: Play(int times) {
    // int Mix_PlayChannel(int channel, Mix_Chunk* chunk, int loops)
    this->channel = Mix_PlayChannel(-1, this->chunk, times-1);
}
void Sound :: Stop() {
    if (this->chunk){
        Mix_HaltChannel(this->channel);    // Para todas as músicas
    }
}
void Sound :: Open(std::string file) {
    this->chunk = Mix_LoadWAV(file.c_str());
    // Obs: retorna null, mas carrega arquivo :/
    if( !chunk )    // nao conseguiu carregar arquivo
        LOG("Sound :: Open(std::string file) : NULL pointer returned\n");
    // LOG( ( "CARREGOU %s\n", file.c_str() ) );
}
bool Sound :: IsOpen() {
    return !!this->chunk;
}

void Sound :: Update(float dt) {
    
}
void Sound :: Render() {
    
}
bool Sound :: Is(std::string type) {
    return type == "Sound";
}
