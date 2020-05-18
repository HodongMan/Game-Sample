#include "pch.h"

#include "Actor.h"
#include "Game.h"
#include "Component.h"


Actor::Actor( Game* game )
	: _state( State::EActive )
	, _position( Vector2::Zero )
	, _scale( 1.0f )
	, _rotation( 0.0f )
	, _game( game )
{
	_game->addActor( this );
}

Actor::~Actor()
{
	_game->removeActor( this );

	while ( false == _components.empty() )
	{
		delete _components.back();
	}
}

void Actor::update( float deltaTime ) noexcept
{
	if ( State::EActive == _state )
	{
		updateComponents( deltaTime );
		updateActor( deltaTime );
	}
}

void Actor::updateComponents( float deltaTime ) noexcept
{
	for ( auto comp : _components )
	{
		comp->update( deltaTime );
	}
}

void Actor::updateActor( float deltaTime ) noexcept
{
	
}

void Actor::processInput( const uint8_t* keyState ) noexcept
{
	if ( State::EActive == _state )
	{
		for ( auto comp : _components )
		{
			comp->processInput( keyState ); 
		}

		actorInput( keyState );
	}
}

void Actor::actorInput( const uint8_t* keyState ) noexcept
{
	
}

void Actor::addComponent( Component* component ) noexcept
{
	int myOrder = component->getUpdateOrder();

	auto iter = _components.begin();

	for ( ; iter != _components.end(); ++iter )
	{
		if ( myOrder < (*iter)->getUpdateOrder() )
		{
			break;
		}
	}

	_components.insert( iter, component );
}

void Actor::removeComponent( Component* component ) noexcept
{
	auto iter = std::find( _components.begin(), _components.end(), component );
	if ( iter != _components.end() )
	{
		_components.erase( iter );
	}
}