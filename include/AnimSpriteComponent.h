#ifndef ANIMSPRITECOMPONENT_H
#define ANIMSPRITECOMPONENT_H

#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent :public SpriteComponent
{
    public:
        AnimSpriteComponent();
        ~AnimSpriteComponent();

        AnimSpriteComponent(class Entity* const owner, int drawOrder = 100);
	    void Update(float deltaTime) override;
        void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
        float GetAnimFPS() const { return mAnimFPS; }
        void SetAnimFPS(float fps) { mAnimFPS = fps; }
        void SetFrameStartAndEnd(int startFrame, int endFrame);

    private:
        std::vector<SDL_Texture*> mAnimTextures;
        float mCurrFrame;
        float mAnimFPS;
        int mFrameStart;
        int mFrameEnd;
};

#endif // ANIMSPRITECOMPONENT_H
