#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent( Actor* owner )
	:MoveComponent( owner )
	, mForwardKey( 0 )
	, mBackKey( 0 )
	, mClockwiseKey( 0 )
	, mCounterClockwiseKey( 0 )
{

}

void InputComponent::processInput( const uint8_t* keyState ) noexcept
{
	float forwardSpeed = 0.0f;
	
	if ( keyState[mForwardKey] )
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if ( keyState[mBackKey] )
	{
		forwardSpeed -= mMaxForwardSpeed;
	}

	setForwardSpeed( forwardSpeed );

	float angularSpeed = 0.0f;
	if ( keyState[mClockwiseKey] )
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if ( keyState[mCounterClockwiseKey] )
	{
		angularSpeed -= mMaxAngularSpeed;
	}

	setAngularSpeed( angularSpeed );
}