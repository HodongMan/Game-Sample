#include "AIState.h"
#include "AIComponent.h"
#include <SDL_log.h>

void AIPatrol::update( float deltaTime ) noexcept
{
	SDL_Log( "Updating %s state", getName() );

	bool dead = true;
	if ( dead )
	{
		mOwner->changeState( "Death" );
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