#pragma once

#include "Actor.h"

class Game;

class Ship : public Actor
{
public:
	Ship( Game* game);

	void updateActor( float deltaTime ) noexcept override;
	void actorInput( const uint8_t* keyState ) noexcept override;

private:
	float mLaserCooldown;
};