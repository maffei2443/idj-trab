#pragma once
#ifndef MACROS_H
#define MACROS_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include <iostream>

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
    std::cerr << "Error passed : " <<  err << "\n";
    abort();
}


#endif