#pragma once

#include "Actor.h"

class Game;

class Ship : public Actor
{
public:
	Ship( Game* game);

	void updateActor( float deltaTime ) noexcept override;
	void processKeyBoard( const uint8_t* state ) noexcept;
	float getRightSpeed( void ) const noexcept { return mRightSpeed;}
	float getDownSpeed( void ) const noexcept { return mDownSpeed; }

private:

	float mRightSpeed;
	float mDownSpeed;
};