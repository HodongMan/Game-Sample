#pragma once

#include <vector>
#include "Math.h"
#include "TypeDefine.h"

class Game;
class Component;

class Actor
{
public:

	Actor( Game* game );
	virtual ~Actor();

	void update( float deltaTime ) noexcept;

	void updateComponents( float deltaTime ) noexcept;

	virtual void updateActor( float deltaTime ) noexcept;

	const Vector2& getPosition( void ) const noexcept { return mPosition; }
	void setPosition( const Vector2& position ) noexcept { mPosition = position; }

	float getScale( void ) const noexcept { return mScale; }
	void setScale( float scale ) noexcept { mScale = scale; }

	float getRotation( void ) const noexcept { return mRotation; }
	void setRotation( float rotation ) noexcept { mRotation = rotation; }

	const State& getState( void ) const noexcept { return mState; }
	void setState( const State& state ) noexcept { mState = state ;}

	Game* getGame( void ) const noexcept { return mGame; }

	void addComponent( Component* component ) noexcept;
	void removeComponent( Component* component ) noexcept;

private:

	State mState;

	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<Component*> mComponents;
	Game* mGame;
};