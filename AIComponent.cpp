#include "pch.h"

#include "AIComponent.h"
#include "Actor.h"
#include "AIState.h"


AIComponent::AIComponent( Actor* owner )
	:Component( owner )
	, _currentState( nullptr )
{
}

void AIComponent::update( float deltaTime ) noexcept
{
	if ( nullptr != _currentState )
	{
		_currentState->update( deltaTime );
	}
}

void AIComponent::changeState( const std::string& name ) noexcept
{
	if ( nullptr != _currentState )
	{
		_currentState->onExit();
	}
	\
	auto iter = _stateMap.find( name );
	if ( iter != _stateMap.end() )
	{
		_currentState = iter->second;

		_currentState->onEnter();
	}
	else
	{
		SDL_Log( "Could not find AIState %s in state map", name.c_str() );
		_currentState = nullptr;
	}
}

void AIComponent::registerState( AIState* state ) noexcept
{
	_stateMap.emplace( state->getName(), state );
}