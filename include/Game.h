#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
    public:
        Game();
        ~Game();


    bool Initialize();
    void RunLoop();
    void Shutdown();

    private:
    void ProcessInput();
    void Update();
    void GenerateOuput();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;
};

#endif // GAME_H
