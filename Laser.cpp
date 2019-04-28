#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"


Laser::Laser( Game* game )
	:Actor( game )
	, mDeathTimer(1.0f)
{
	SpriteComponent* sc = new SpriteComponent( this );
	sc->setTexture( game->getTexture( "Assets/Laser.png" ) );

	MoveComponent* mc = new MoveComponent( this );
	mc->setForwardSpeed( 800.0f );

	mCircle = new CircleComponent( this );
	mCircle->setRadius( 11.0f );
}

void Laser::updateActor( float deltaTime ) noexcept
{
	mDeathTimer -= deltaTime;

	if ( mDeathTimer <= 0.0f )
	{
		setState( State::EDead );
	}
	else
	{
		for ( auto ast : getGame()->getAsteroids() )
		{
			if ( Intersect( *mCircle, *( ast->getCircle() ) ) )
			{
				setState( State::EDead );
				ast->setState( State::EDead );
				
				break;
			}
		}
	}
}