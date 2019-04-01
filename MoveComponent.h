#pragma once
#include "Component.h"

class Actor;

class MoveComponent : public Component
{
public:
	MoveComponent( Actor* owner, int updateOrder = 10 );

	void		update( float deltaTime ) noexcept override;

	float		getAngularSpeed( void ) const noexcept { return mAngularSpeed; }
	float		getForwardSpeed( void ) const noexcept { return mForwardSpeed; }

	void		setAngularSpeed( float speed ) noexcept { mAngularSpeed = speed; }
	void		setForwardSpeed( float speed ) noexcept { mForwardSpeed = speed; }

private:

	float		mAngularSpeed;
	float		mForwardSpeed;
};