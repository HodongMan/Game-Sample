#pragma once

#include "Actor.h"

class Game;
class CircleComponent;


class Bullet : public Actor
{
public:
	Bullet( Game* game );
	void updateActor( float deltaTime ) noexcept override;

private:
	CircleComponent* _circle;
	float _liveTime;
};