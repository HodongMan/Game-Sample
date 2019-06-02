#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <algorithm>

Enemy::Enemy( Game* game )
	:Actor( game )
{
	game->getEnemies().emplace_back( this );
	
	SpriteComponent* sc = new SpriteComponent( this );
	sc->setTexture( game->getTexture( "Assets/Airplane.png" ) );

	setPosition( getGame()->getGrid()->getStartTile()->getPosition() );
	
	NavComponent* nc = new NavComponent( this );
	nc->SetForwardSpeed(150.0f);
	nc->StartPath( getGame()->getGrid()->getStartTile() );

	mCircle = new CircleComponent( this );
	mCircle->setRadius( 25.0f );
}

Enemy::~Enemy( void )
{
	auto iter = std::find( getGame()->getEnemies().begin(), getGame()->getEnemies().end(), this );
	
	getGame()->getEnemies().erase( iter );
}

const CircleComponent* Enemy::getCircle( void ) const noexcept
{
	return mCircle;
}

void Enemy::updateActor( float deltaTime ) noexcept
{
	Actor::updateActor( deltaTime );
	
	Vector2 diff = getPosition() - getGame()->getGrid()->getEndTile()->getPosition();
	if ( Math::NearZero( diff.Length(), 10.0f ) )
	{
		setState( State::EDead );
	}
}