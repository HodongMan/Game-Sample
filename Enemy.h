#pragma once
#include "Actor.h"

class Game;
class CircleComponent;

class Enemy : public Actor
{
public:
	Enemy( Game* game );
	~Enemy( void );
	void updateActor(float deltaTime) noexcept override;
	const CircleComponent* getCircle( void ) const noexcept;

private:
	CircleComponent* mCircle;
};