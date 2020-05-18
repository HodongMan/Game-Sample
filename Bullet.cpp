#include "pch.h"

#include "Bullet.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Enemy.h"

Bullet::Bullet( Game* game )
	: Actor( game )
{
	SpriteComponent* sc = new SpriteComponent( this );
	sc->setTexture( game->getTexture( "Assets/Projectile.png" ) );
	
	MoveComponent* mc = new MoveComponent( this );
	mc->setForwardSpeed( 400.0f );
	
	_circle = new CircleComponent(this);
	_circle->setRadius( 5.0f );
	
	_liveTime = 1.0f;
}

void Bullet::updateActor( float deltaTime ) noexcept
{
	Actor::updateActor( deltaTime );
	
	for ( Enemy* e : getGame()->getEnemies() )
	{
		if (Intersect( *_circle, *(e->getCircle() ) ) )
		{
			e->setState( State::EDead );
			setState( State::EDead );
			break;
		}
	}
	
	_liveTime -= deltaTime;
	if ( _liveTime <= 0.0f )
	{
		setState( State::EDead );
	}
}