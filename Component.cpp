#include "Component.h"
#include "Actor.h"

Component::Component( Actor* owner, int updateOrder )
	: mOwner( owner )
	, mUpdateOrder( updateOrder )
{
	mOwner->addComponent( this );
}

Component::~Component()
{
	mOwner->removeComponent( this );
}

void Component::update( float deltaTime ) noexcept
{

}