#include <string>
#define INCLUDE_SDL // main. sdl. func
#include "SDL_include.h"
#define GAME_CHANNELS 32
// TODO: Create class to store "magic numbers" constants.

class Game {
    private:
        int width;
        int height;
        std::string title;
        Game(std::string title, int width, int height );
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        // State* state;
    public:
        ~Game();
        void Run();
        SDL_Renderer* SDL_GetRenderer();
        // State& GetState();
        Game& GetInstance();
};

