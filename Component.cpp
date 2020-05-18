#include "pch.h"

#include "Component.h"
#include "Actor.h"

Component::Component( Actor* owner, int updateOrder )
	: _owner( owner )
	, _updateOrder( updateOrder )
{
	_owner->addComponent( this );
}

Component::~Component()
{
	_owner->removeComponent( this );
}

void Component::update( float deltaTime ) noexcept
{

}