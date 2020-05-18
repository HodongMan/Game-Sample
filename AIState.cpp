#include "pch.h"

#include "AIState.h"
#include "AIComponent.h"

void AIPatrol::update( float deltaTime ) noexcept
{
	SDL_Log( "Updating %s state", getName() );

	bool dead = true;
	if ( dead )
	{
		_owner->changeState( "Death" );
	}
}

void AIPatrol::onEnter( void ) noexcept
{
	SDL_Log( "Entering %s state", getName() );
}

void AIPatrol::onExit( void ) noexcept
{
	SDL_Log( "Exiting %s state", getName() );
}

void AIDeath::update( float deltaTime ) noexcept
{
	SDL_Log( "Updating %s state", getName() );
}

void AIDeath::onEnter( void ) noexcept
{
	SDL_Log( "Entering %s state", getName() );
}

void AIDeath::onExit( void ) noexcept
{
	SDL_Log( "Exiting %s state", getName() );
}

void AIAttack::update( float deltaTime ) noexcept
{
	SDL_Log( "Updating %s state", getName() );
}

void AIAttack::onEnter( void ) noexcept
{
	SDL_Log( "Entering %s state", getName() );
}

void AIAttack::onExit( void ) noexcept
{
	SDL_Log( "Exiting %s state", getName() );
}