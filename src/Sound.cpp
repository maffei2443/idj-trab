#include "Sound.h"
#include "GameObject.h"
#include <exception>
#include <iostream>

int AuxCodeErr = 0;
#ifndef SDL_ABORT_IF_NZERO
    #define SDL_ABORT_IF_NZERO( x ) \
        AuxCodeErr = x; if (AuxCodeErr) myAbort(AuxCodeErr); else printf("Ok passed.\n");
#endif
#ifndef SDL_ABORT_IF_ZERO
    #define SDL_ABORT_IF_ZERO( x ) \
            SDL_ABORT_IF_NZERO(!(x) )
#endif
void myAbort(int err) {
    std::cerr << "SDL error : " << SDL_GetError() << "\n";
    std::cerr << "Error passed : " <<  err << "\n";
    abort();
}


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
    this->Stop();
    // void Mix_FreeChunk(Mix_Chunk* chunk)
    Mix_FreeChunk(this->chunk);
}
void Sound :: Play(int times) {
    // int Mix_PlayChannel(int channel, Mix_Chunk* chunk, int loops)
    if(this->chunk)
        std::cerr << "Impossivel desalocar proximos canais individualmente [Sound.Play]" << std::endl;
    this->channel = Mix_PlayChannel(-1, this->chunk, times);
}
void Sound :: Stop() {
    // int Mix_HaltChannel(int channel)
    if (this->chunk)
        Mix_HaltChannel(this->channel);    // Para todas as músicas
}
void Sound :: Open(std::string file) {
    // Mix_Chunk* Mix_LoadWAV(char* file);
    this->chunk = Mix_LoadWAV(file.c_str());
    if( !chunk )    // nao conseguiu carregar arquivo
        throw "Sound :: Open(std::string file) : NULL pointer returned";
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
