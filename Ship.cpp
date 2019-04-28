#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"


Ship::Ship( Game* game )
	: Actor( game )
	, mLaserCooldown( 0.0f )
{
	SpriteComponent* sc = new SpriteComponent( this, 150 );
	sc->setTexture( game->getTexture( "Assets/Ship.png" ) );

	InputComponent* ic = new InputComponent( this );
	ic->setForwardKey( SDL_SCANCODE_W );
	ic->setBackKey( SDL_SCANCODE_S );
	ic->setClockwiseKey( SDL_SCANCODE_A );
	ic->setCounterClockwiseKey( SDL_SCANCODE_D );
	ic->setMaxForwardSpeed( 300.0f );
	ic->setMaxAngularSpeed( Math::TwoPI );
}

void Ship::updateActor( float deltaTime ) noexcept
{
	mLaserCooldown -= deltaTime;
}

void Ship::actorInput( const uint8_t* keyState ) noexcept
{
	if ( keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f )
	{
		Laser* laser = new Laser( getGame() );
		laser->setPosition( getPosition() );
		laser->setRotation( getRotation() );
		
		mLaserCooldown = 0.5f;
	}
}