#include "Macros.h"

#define INCLUDE_SDL
#include "SDL_include.h"

int AuxCodeErr = 0;

void myAbort(int err) {
    std::cerr << "SDL error : " << SDL_GetError() << "\n";
    std::cerr << "Error passed : " <<  err << "\n";
    abort();
}