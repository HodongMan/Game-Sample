#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"


Asteroid::Asteroid( Game* game )
	: Actor( game )
	, mCircle( nullptr )
{
	Vector2 randPos = Random::getVector( Vector2::Zero, Vector2( 1024.f, 768.f ) );

	setPosition( randPos );
	setRotation( Random::getFloatRange( 0.0f, Math::TwoPI ) );

	SpriteComponent* sc = new SpriteComponent( this );
	sc->setTexture( game->getTexture( "Assets/Asteroid.png" ) );

	MoveComponent* mc = new MoveComponent( this );
	mc->setForwardSpeed( 150.0f );
	
	mCircle = new CircleComponent( this );
	mCircle->setRadius( 40.0f );

	game->addAsteroid( this );
}

Asteroid::~Asteroid()
{
	getGame()->removeAsteroid( this );
}