#ifndef ANIMSPRITESHEETCOMPONENT_H
#define ANIMSPRITESHEETCOMPONENT_H

#include "SpriteComponent.h"
#include "Math.h"

class AnimSpriteSheetComponent : public SpriteComponent
{
    public:
        AnimSpriteSheetComponent(class Entity* const owner, int drawOrder = 100);
        ~AnimSpriteSheetComponent();

        void Update(float deltaTime) override;
	    void Draw(SDL_Renderer* renderer) override;
	    void SetFrameStartAndEnd(int startFrame, int endFrame);

	    float GetAnimFPS() const { return mAnimFPS; }
	    void SetAnimFPS(float fps) { mAnimFPS = fps; }
	    void SetImageWidth(int width) {mTextureWidth = width;}
	    void SetImageHeight(int Height) {mTextureHeight = Height;}
        void SetSpriteWidth(int width) {mSpriteWidth = width;}
	    void SetSpriteHeight(int height) {mSpriteHeight = height;}


    private:
        float mCurrFrame;
        float mAnimFPS;
        int mFrameStart;
        int mFrameEnd;
        int mSpriteWidth;
        int mSpriteHeight;
        Vector2 mStartPos;
        Vector2 mEndPos;
};

#endif // ANIMSPRITESHEETCOMPONENT_H
