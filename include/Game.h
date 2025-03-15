#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class Game
{
    public:
        Game();
        ~Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddEntity(std::unique_ptr<class Entity> entity);

    private:
    void ProcessInput();
    void Update();
    void GenerateOuput();
    void UpdateEntities(float deltaTime);
    void LoadData();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;
    bool mUpdatingEntities;

    std::vector<std::unique_ptr<class Entity>> mEntities;
	std::vector<std::unique_ptr<class Entity>> mPendingEntities;
	std::vector<std::unique_ptr<class Component>> mSprites;

    std::string mGameTitle = "Dolphin 2D";
};

#endif // GAME_H
