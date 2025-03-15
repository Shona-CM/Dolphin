#include "Component.h"
#include "Entity.h"

Component::Component(Entity* const owner, int updateOrder)
    :mOwner(owner)
	,mUpdateOrder(updateOrder)
{
    mId = reinterpret_cast<std::uintptr_t>(this);
    std::cout << "Create Component" << '\n';
}

Component::~Component()
{
    std::cout << "Delete Component" << '\n';
}

