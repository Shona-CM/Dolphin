#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "SpriteComponent.h"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
    public:
        SpriteComponent(Entity* const owner, int drawOrder);
        virtual ~SpriteComponent();

        virtual void Draw(SDL_Renderer* mRenderer);
        virtual void SetTexture(SDL_Texture* texture);

        void SetTextureWidth(int width) {mTextureWidth = width;}
	    void SetTextureHeight(int height) {mTextureHeight = height;}
	    int GetTextureWidth() const { return mTextureWidth; }
	    int GetTextureHeight() const { return mTextureHeight; }

    protected:
        int mTextureWidth;
        int mTextureHeight;
        SDL_Texture* mTexture;
};

#endif // SPRITECOMPONENT_H
