#pragma once
#include "MoveComponent.h"
#include <cstdint>


class Actor;

class InputComponent : public MoveComponent
{
public:

	InputComponent( Actor* owner );

	void			processInput( const uint8_t* keyState ) noexcept override;
	float			getMaxForward( void ) const noexcept { return mMaxForwardSpeed; }
	float			getMaxAngular( void ) const noexcept { return mMaxAngularSpeed; }
	int				getForwardKey( void ) const noexcept { return mForwardKey; }
	int				getBackKey( void ) const noexcept { return mBackKey; }
	int				getClockwiseKey( void ) const noexcept { return mClockwiseKey; }
	int				getCounterClockwiseKey( void ) const noexcept { return mCounterClockwiseKey; }

	void			setMaxForwardSpeed( float speed ) noexcept { mMaxForwardSpeed = speed; }
	void			setMaxAngularSpeed( float speed ) noexcept { mMaxAngularSpeed = speed; }
	void			setForwardKey( int key ) noexcept { mForwardKey = key; }
	void			setBackKey( int key ) noexcept { mBackKey = key; }
	void			setClockwiseKey( int key ) noexcept { mClockwiseKey = key; }
	void			setCounterClockwiseKey( int key ) noexcept { mCounterClockwiseKey = key; }

private:

	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	int mForwardKey;
	int mBackKey;
	int mClockwiseKey;
	int mCounterClockwiseKey;

};