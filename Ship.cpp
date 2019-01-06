#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"


Ship::Ship( Game* game )
	: Actor( game )
	, mRightSpeed( 0.0f )
	, mDownSpeed( 0.0f )
{
	AnimSpriteComponent* asc = new AnimSpriteComponent( this );

	std::vector<SDL_Texture*> anims = {
		game->getTexture( "Assets/Ship01.png" ),
		game->getTexture( "Assets/Ship02.png" ),
		game->getTexture( "Assets/Ship03.png" ),
		game->getTexture( "Assets/Ship04.png" ),
	};

	asc->setAnimTextures( anims );
}

void Ship::updateActor( float deltaTime ) noexcept
{
	Actor::updateActor( deltaTime );

	Vector2 position = getPosition();

	position.x = mRightSpeed * deltaTime;
	position.y = mDownSpeed * deltaTime;

	if ( position.x < 25.0f )
	{
		position.x = 25.0f;
	}
	else if ( 500.0f < position.x )
	{
		position.x = 500.0f;
	}
	if ( position.y < 25.0f )
	{
		position.y = 25.0f;
	}
	else if ( 743.0f < position.y )
	{
		position.y = 743.0f;
	}

	setPosition( position );
}

void Ship::processKeyBoard( const uint8_t* state ) noexcept
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	
	if ( state[SDL_SCANCODE_D] )
	{
		mRightSpeed += 250.0f;
	}
	if ( state[SDL_SCANCODE_A] )
	{
		mRightSpeed -= 250.0f;
	}

	if ( state[SDL_SCANCODE_S] )
	{
		mDownSpeed += 300.0f;
	}
	if ( state[SDL_SCANCODE_W] )
	{
		mDownSpeed -= 300.0f;
	}
}