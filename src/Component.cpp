#include "Component.h"
#include "Entity.h"

#include <iostream>

Component::Component(Entity* const owner, int updateOrder)
    :mOwnerEntity(owner)
	,mUpdateOrder(updateOrder)
{
    mId = reinterpret_cast<std::uintptr_t>(this);
    std::cout << "Create Component" << '\n';
}

Component::~Component()
{
    std::cout << "Delete Component" << '\n';
}

void Component::Update(float deltaTime)
{
}
