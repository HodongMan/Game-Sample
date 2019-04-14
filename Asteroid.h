#pragma once

#include "Actor.h"

class Game;
class CircleComponent;

class Asteroid : public Actor
{
public:
	Asteroid( class Game* game );
	~Asteroid( void );

	const CircleComponent * getCircle( void ) const noexcept { return mCircle; }

private:

	CircleComponent*		mCircle;
};