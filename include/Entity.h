#ifndef ENTITY_H
#define ENTITY_H

#include "Math.h"
#include "Component.h"

#include <string>
#include <vector>
#include <memory>


class Entity
{
    public:

    	enum State
        {
            EActive,
            EPaused,
            EInActive
        };

        Entity(class Game* const game);
        virtual ~Entity();
        Entity(const Entity&) = delete;


        void Update(float deltaTime);
        void UpdateComponents(float deltaTime);
        //override to do Entity specific updates
	    virtual void UpdateEntity(float deltaTime);

	    //basic move ,rotate and scale
	    const Vector2& GetPosition() const { return mPosition; }
        void SetPosition(const Vector2& pos) { mPosition = pos; }
        float GetScale() { return mScale; }
        void SetScale(float scale) { mScale = scale; }
        float GetRotation() { return mRotation; }
        void SetRotation(float rotation) { mRotation = rotation; }
        bool GetIsGoingBackwards()  {return mIsGoingBackwards;}

        //State
        State GetState() { return mState; }
        void SetState(State state) { mState = state; }

        //Name
         std::string const GetName() { return mName; }
         void SetName(std::string name) { mName = name; }

         // Game - non ownership
        class Game* const GetGame() { return mGame; }


        // Add/remove components
        void AddComponent(std::unique_ptr<class Component> component);
        void RemoveComponent(std::uintptr_t);

	protected:
        bool mIsGoingBackwards;

    private:
        State mState;
        // Transform
        Vector2 mPosition;
        float mScale;
        float mRotation;
        std::string mName;

        // store our components here
        std::vector<std::unique_ptr<class Component>> mComponents;
        class Game* const mGame;
};

#endif // ENTITY_H
