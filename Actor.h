#pragma once

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

	void processInput( const uint8_t* keyState ) noexcept;

	virtual void actorInput( const uint8_t* keyState ) noexcept;

	const Vector2& getPosition( void ) const noexcept { return _position; }
	void setPosition( const Vector2& position ) noexcept { _position = position; }

	float getScale( void ) const noexcept { return _scale; }
	void setScale( float scale ) noexcept { _scale = scale; }

	float getRotation( void ) const noexcept { return _rotation; }
	void setRotation( float rotation ) noexcept { _rotation = rotation; }

	Vector2 getForward( void ) const noexcept { return Vector2( Math::Cos( _rotation ), -Math::Sin( _rotation ) ); }

	const State& getState( void ) const noexcept { return _state; }
	void setState( const State& state ) noexcept { _state = state ;}

	Game* getGame( void ) const noexcept { return _game; }

	void addComponent( Component* component ) noexcept;
	void removeComponent( Component* component ) noexcept;

private:

	State _state;

	Vector2 _position;
	float _scale;
	float _rotation;

	std::vector<Component*> _components;
	Game* _game;
};