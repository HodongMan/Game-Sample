#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor( Game* game )
	: mState( State::EActive )
	, mPosition( Vector2::Zero )
	, mScale( 1.0f )
	, mRotation( 0.0f )
	, mGame( game )
{
	mGame->addActor( this );
}

Actor::~Actor()
{
	mGame->removeActor( this );

	while ( false == mComponents.empty() )
	{
		delete mComponents.back();
	}
}

void Actor::update( float deltaTime ) noexcept
{
	if ( State::EActive == mState )
	{
		updateComponents( deltaTime );
		updateActor( deltaTime );
	}
}

void Actor::updateComponents( float deltaTime ) noexcept
{
	for ( auto comp : mComponents )
	{
		comp->update( deltaTime );
	}
}

void Actor::updateActor( float deltaTime ) noexcept
{
	
}

void Actor::processInput( const uint8_t* keyState ) noexcept
{
	if ( State::EActive == mState )
	{
		for ( auto comp : mComponents )
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

	auto iter = mComponents.begin();

	for ( ; iter != mComponents.end(); ++iter )
	{
		if ( myOrder < (*iter)->getUpdateOrder() )
		{
			break;
		}
	}

	mComponents.insert( iter, component );
}

void Actor::removeComponent( Component* component ) noexcept
{
	auto iter = std::find( mComponents.begin(), mComponents.end(), component );
	if ( iter != mComponents.end() )
	{
		mComponents.erase( iter );
	}
}