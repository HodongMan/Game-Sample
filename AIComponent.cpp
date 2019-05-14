#include "AIComponent.h"
#include "Actor.h"
#include "AIState.h"
#include <SDL_log.h>

AIComponent::AIComponent( Actor* owner )
	:Component( owner )
	, mCurrentState( nullptr )
{
}

void AIComponent::update( float deltaTime ) noexcept
{
	if ( nullptr != mCurrentState )
	{
		mCurrentState->update( deltaTime );
	}
}

void AIComponent::changeState( const std::string& name ) noexcept
{
	if ( nullptr != mCurrentState )
	{
		mCurrentState->onExit();
	}
	\
	auto iter = mStateMap.find( name );
	if ( iter != mStateMap.end() )
	{
		mCurrentState = iter->second;

		mCurrentState->onEnter();
	}
	else
	{
		SDL_Log( "Could not find AIState %s in state map", name.c_str() );
		mCurrentState = nullptr;
	}
}

void AIComponent::registerState( AIState* state ) noexcept
{
	mStateMap.emplace( state->getName(), state );
}