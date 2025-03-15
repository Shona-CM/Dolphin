// Animation sprite class is a component that contains a single texture containing the images
// for a single animation.
// Derives from Sprite component for access to width,height and texture.

#include "AnimSpriteSheetComponent.h"
#include "Entity.h"

AnimSpriteSheetComponent::AnimSpriteSheetComponent(Entity* const owner, int drawOrder)
    :SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
	, mFrameStart(0)
	, mFrameEnd(0)
{
    std::cout << "Create Animated SpriteSheet Component" << '\n';
}

AnimSpriteSheetComponent::~AnimSpriteSheetComponent()
{
    std::cout << "Delete SpriteSheet Component" << '\n';
}

void AnimSpriteSheetComponent::SetFrameStartAndEnd(int startFrame, int endFrame)
{
   //sanitize input
   mFrameStart = startFrame;
   mFrameEnd = endFrame;


   if(mFrameStart == mFrameEnd)
   {
     mFrameEnd += 1;
   }
   else if(startFrame > endFrame)
   {
     mFrameStart = endFrame;
     mFrameEnd = startFrame;
   }
}


void AnimSpriteSheetComponent::Draw(SDL_Renderer* renderer)
{
   // get source location in sprite sheet
   int numberOfSpritesPerLine = mTextureWidth / mSpriteWidth;
   int framePos = static_cast<int>(mCurrFrame);
   int startLine = static_cast<int>(framePos/ numberOfSpritesPerLine);
   int startX = static_cast<int>(framePos * mSpriteWidth) - static_cast<int>(startLine * mTextureWidth);

   SDL_Rect source_rect;
   source_rect.w = mSpriteWidth;
   source_rect.h = mSpriteHeight;
   source_rect.x = startX;
   source_rect.y = startLine * mSpriteHeight;


    if (mTexture)
	{
		SDL_Rect dest_rect;
		dest_rect.w = static_cast<int>(mSpriteWidth * mOwner->GetScale());
		dest_rect.h = static_cast<int>(mSpriteHeight * mOwner->GetScale());
		dest_rect.x = static_cast<int>(mOwner->GetPosition().x - dest_rect.w / 2);
		dest_rect.y = static_cast<int>(mOwner->GetPosition().y - dest_rect.h / 2);


        auto flip = SDL_FLIP_NONE;
        if(mOwner->GetIsGoingBackwards())
            flip = SDL_FLIP_HORIZONTAL;

		SDL_RenderCopyEx(renderer,
			mTexture,
			&source_rect,
			&dest_rect,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			flip);
	}
}

void AnimSpriteSheetComponent::Update(float deltaTime)
{
	   SpriteComponent::Update(deltaTime);

		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		// Wrap current frame if needed
		while (mCurrFrame >= mFrameEnd)
		{
			mCurrFrame -= mFrameEnd;
		}

		if(mCurrFrame > mFrameEnd)
            mCurrFrame = mFrameEnd;
        else if(mCurrFrame < mFrameStart)
            mCurrFrame = mFrameStart;
}

