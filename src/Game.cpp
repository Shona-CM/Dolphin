
#include "Game.h"
#include "Entity.h"
#include "SpriteComponent.h"

#include <algorithm>
#include <iostream>
#include <string>

Game::Game():
mWindow(nullptr),
mRenderer(nullptr),
mIsRunning(true),
mUpdatingEntities(false)
{
    std::cout << "Create Game" << '\n';
}

Game::~Game()
{
   std::cout << "Pending clear " << '\n';
   mPendingEntities.clear();
   std::cout << "Entities clear " << '\n';
   mEntities.clear();
   std::cout << "Delete Game " << '\n';
}


bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult != 0)
    {std::vector<class Entity*> mEntities;
	std::vector<class Entity*> mPendingEntities;
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        mGameTitle.c_str() , // Window title
        100,// Top left x-coordinate of window
        100,// Top left y-coordinate of window
        1024, // Width of window
        768, // Height of window
        0   // Flags (0 for no flags set)
        );

    if(!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    LoadData();

    return true;
}

void Game::LoadData()
{
    std::unique_ptr<Entity> temp = std::make_unique<Entity>(this);
    temp->SetName("test object");
    temp->SetPosition(Vector2(400.0f, 384.0f));
    auto tempSprite =  std::make_unique<SpriteComponent>(temp.get(),50);
    temp->AddComponent(std::move(tempSprite));
    AddEntity(std::move(temp));

    std::unique_ptr<Entity> temp2 = std::make_unique<Entity>(this);
    temp2->SetName("test object 2");
    temp2->SetPosition(Vector2(400.0f, 384.0f));
    temp2->SetState(Entity::EInActive);
    AddEntity(std::move(temp2));

    std::unique_ptr<Entity> temp3 = std::make_unique<Entity>(this);
    temp3->SetName("test object 3");
    temp3->SetPosition(Vector2(400.0f, 384.0f));
    temp3->SetState(Entity::EInActive);
    AddEntity(std::move(temp3));
}

void Game::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop()
{
    while(mIsRunning)
    {
        ProcessInput();
        Update();
        GenerateOuput();
    }
}

void  Game::ProcessInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }

    // Get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::Update()
{
    // Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
	;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

    UpdateEntities(deltaTime);
}

void Game::GenerateOuput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        0,0,255,255);

    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);
}


void Game::AddEntity(std::unique_ptr<Entity> entity)
{
	if (mUpdatingEntities)
	{
		mPendingEntities.emplace_back(std::move(entity));
	}
	else
	{
		mEntities.emplace_back(std::move(entity));
	}
}

void  Game::UpdateEntities(float deltaTime)
{
    mUpdatingEntities = true;

	for (auto& entity : mEntities)
	{
		entity->Update(deltaTime);
	}

	mUpdatingEntities = false;

	// add pending entities to main list.
	for (auto& pending : mPendingEntities)
	{
		mEntities.push_back(std::move(pending));
	}
	mPendingEntities.clear();

	//remove inactive entities
	mEntities.erase(
        std::remove_if(mEntities.begin(), mEntities.end(),
        [](auto& x) {return x->GetState() == Entity::EInActive;}),
    mEntities.end());
}




