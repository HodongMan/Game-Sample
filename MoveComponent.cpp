#include "MoveComponent.h"
#include "Actor.h"


MoveComponent::MoveComponent( Actor* owner, int updateOrder )
	: Component( owner, updateOrder )
	, mAngularSpeed( 0.0f )
	, mForwardSpeed( 0.0f )
{

}

void MoveComponent::update( float deltaTime ) noexcept
{
	if ( false == Math::NearZero( mAngularSpeed ) )
	{
		float rotation	= mOwner->getRotation();
		rotation		+= mAngularSpeed * deltaTime;

		mOwner->setRotation( rotation );
	}

	if ( false == Math::NearZero( mForwardSpeed ) )
	{
		Vector2 position	= mOwner->getPosition();
		position			+= mOwner->getForward() * mForwardSpeed * deltaTime;

		if ( position.x < 0.0f )
		{ 
			position.x = 1022.0f;
		}
		else if ( position.x > 1024.0f ) 
		{ 
			position.x = 2.0f; 
		}

		if ( position.y < 0.0f ) 
		{
			position.y = 766.0f; 
		}
		else if ( position.y > 768.0f ) 
		{
			position.y = 2.0f; 
		}

		mOwner->setPosition( position );
	}
}