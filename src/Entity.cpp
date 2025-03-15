#include "Entity.h"
#include "Game.h"

#include <algorithm>
#include <iostream>

Entity::Entity(Game* game)
    : mIsGoingBackwards(false)
    , mState(EActive)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)

{
     std::cout  <<  "Create Entity" <<  '\n';
}

Entity::~Entity()
{
    std::cout  <<  "clear all " <<  '\n';
    mComponents.clear();
    std::cout << "Delete Entity" << '\n';
}


//Updaters
void Entity::Update(float deltaTime)
{
    if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateEntity(deltaTime);
	}

}

void Entity::UpdateComponents(float deltaTime)
{
    for(const auto& component : mComponents)
    {
       component->Update(deltaTime);
    }
}

void Entity::Draw(SDL_Renderer* renderer)
{
    DrawComponents(renderer);
}

void Entity::DrawComponents(SDL_Renderer* renderer)
{
    for(const auto& component : mComponents)
    {
       component->Draw(renderer);
    }
}

void Entity::UpdateEntity(float deltaTime)
{
}


void Entity::AddComponent(std::unique_ptr<Component> component)
{
	// Find the insertion point in the sorted vector
    // (The first element with a order higher than me)
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (;iter != mComponents.end();++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }

    // Inserts element before position of iterator
    mComponents.insert(iter,std::move(component));

    std::cout << "Number of components " << mComponents.size() << '\n';
}

void Entity::RemoveComponent(std::uintptr_t id)
{
   //remove inactive entities
	mComponents.erase(
        std::remove_if(mComponents.begin(), mComponents.end(),
        [id](auto& x) {return x->GetId() == id;}),
    mComponents.end());
}

