//This component is for animated sprites supplied as individual images
// Has its own texture list.
// detived from SpriteComponent.


#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Entity* const owner, int drawOrder)
    :SpriteComponent(owner, drawOrder)
	,mCurrFrame(0.0f)
	,mAnimFPS(24.0f)
	,mFrameStart(0)
	,mFrameEnd(0)
{
    std::cout << "Create AnimSprite Component" << '\n';
}

AnimSpriteComponent::~AnimSpriteComponent()
{
    std::cout << "Delete AnimSprite Component" << '\n';
}


void AnimSpriteComponent::SetFrameStartAndEnd(int startFrame, int endFrame)
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

   if (mAnimTextures.size() > 0)
   {
      if(mFrameEnd > static_cast<int>(mAnimTextures.size()))
        mFrameEnd = mAnimTextures.size();
   }
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		// Wrap current frame if needed
		while (mCurrFrame >= mFrameEnd)
		{
			mCurrFrame -= mFrameEnd;
		}

		// Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);

		if(mCurrFrame > mFrameEnd)
            mCurrFrame = mFrameEnd;
        else if(mCurrFrame < mFrameStart)
            mCurrFrame = mFrameStart;
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}


