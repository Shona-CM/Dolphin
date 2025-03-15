#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>
#include <iostream>
#include "SDL2/SDL.h"

class Component
{
    public:
        Component(class Entity* const owner, int updateOrder = 100);
        virtual ~Component();

        virtual void Update(float deltaTime) {};
        virtual void Draw(SDL_Renderer* mRenderer) {};

	    int GetUpdateOrder() const { return mUpdateOrder; }
        std::uintptr_t GetId() const {return mId;}

    protected:
        class Entity* const mOwner;
        // defines the order in which the components are updated
        int mUpdateOrder;
        std::uintptr_t  mId;
};

#endif // COMPONENT_H
