//This component can place a single sprite on the screen
// Used for placing platforms , objects etc
// This sprite is not animated.
//Dervied from component.

#include "SpriteComponent.h"
#include "Entity.h"



SpriteComponent::SpriteComponent(Entity* const owner, int drawOrder):Component(owner,drawOrder)
    ,mTextureWidth(0)
    ,mTextureHeight(0)
{
    std::cout << "Create Sprite Component" << '\n';
}

SpriteComponent::~SpriteComponent()
{
    std::cout << "Delete Sprite Component" << '\n';
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		r.w = static_cast<int>(mTextureWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTextureHeight * mOwner->GetScale());
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		auto flip = SDL_FLIP_NONE;
		if(mOwner->GetIsGoingBackwards())
            flip = SDL_FLIP_HORIZONTAL;


		SDL_RenderCopyEx(renderer,
			mTexture,
			nullptr,
			&r,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			flip);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}
