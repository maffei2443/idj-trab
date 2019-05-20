#ifndef MACROS_H
#define MACROS_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include <iostream>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define SPACE_KEY 32

extern int AuxCodeErr;

#ifndef SDL_ABORT_IF_NZERO
    #define SDL_ABORT_IF_NZERO( x ) \
        AuxCodeErr = x; if (AuxCodeErr) myAbort(AuxCodeErr);/*  else //////printf("Ok passed.\n"); */
#endif
#ifndef SDL_ABORT_IF_ZERO
    #define SDL_ABORT_IF_ZERO( x ) \
            SDL_ABORT_IF_NZERO(not (x) )
#endif

void myAbort(int);
#define LOG(x) printf("[Log] "),printf(x);

#ifndef STR
#define STR(x) #x
#define PRINT(expr) cout << STR(expr) ": " << (expr) << endl;
#endif

#endif