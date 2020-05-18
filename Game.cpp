#include "pch.h"

#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"
#include "Enemy.h"


Game::Game( void )
	: _window( nullptr )
	, _renderer( nullptr )
	, _isRunning( true )
	, _updatingActors( false )
{

}

bool Game::initialize( void ) noexcept
{
	if ( 0 != SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) )
	{
		SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );

		return false;
	}
	
	_window = SDL_CreateWindow( "Test", 100, 100, 1024, 768, 0 );
	if ( nullptr == _window )
	{
		SDL_Log( "Failed to create window: %s", SDL_GetError() );

		return false;
	}

	_renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( nullptr == _renderer )
	{
		SDL_Log( "Failed to create renderer: %s", SDL_GetError() );

		return false;
	}
	
	if ( 0 == IMG_Init( IMG_INIT_PNG ) )
	{
		SDL_Log( "Unable to initialize SDL_image: %s", SDL_GetError() );

		return false;
	}
	
	Random::init();

	loadData();

	_ticksCount = SDL_GetTicks();

	return true;
}

void Game::runLoop( void ) noexcept
{
	while ( true == _isRunning )
	{
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::processInput( void ) noexcept
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
		case SDL_QUIT:
			{
				_isRunning = false;
			}
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState( nullptr );
	if ( keyState[SDL_SCANCODE_ESCAPE] )
	{
		_isRunning = false;
	}

	if ( keyState[SDL_SCANCODE_B] )
	{
		_grid->buildTower();
	}

	int x, y;
	const Uint32 buttons = SDL_GetMouseState( &x, &y );
	if ( SDL_BUTTON( buttons ) & SDL_BUTTON_LEFT)
	{
		_grid->processClick( x, y );
	}

	_updatingActors = true;

	for ( auto actor : _actors )
	{
		actor->processInput( keyState );
	}

	_updatingActors = false;
}

void Game::updateGame( void ) noexcept
{
	while ( false == SDL_TICKS_PASSED( SDL_GetTicks(), _ticksCount + 16 ) )
		;

	float deltaTime = ( SDL_GetTicks() - _ticksCount ) / 1000.0f;
	if ( 0.05f < deltaTime )
	{
		deltaTime = 0.05f;
	}

	_ticksCount = SDL_GetTicks();

	_updatingActors = true;
	
	for ( auto actor : _actors )
	{
		actor->update( deltaTime );
	}

	_updatingActors = false;

	for ( auto pending : _pendingActors )
	{
		_actors.emplace_back( pending );
	}
	_pendingActors.clear();

	std::vector<Actor*> deadActors;
	for ( auto actor : _actors )
	{
		if ( State::EDead == actor->getState() )
		{
			deadActors.emplace_back( actor );
		}
	}

	for ( auto actor : deadActors )
	{
		delete actor;
	}
}

void Game::generateOutput( void ) noexcept
{
	SDL_SetRenderDrawColor( _renderer, 0, 0, 0, 255 );
	SDL_RenderClear( _renderer );

	for ( auto sprite : _sprites )
	{
		sprite->draw( _renderer );
	}

	SDL_RenderPresent( _renderer );
}

void Game::loadData( void ) noexcept
{
	_grid = new Grid(this);

	/*
	Actor* a = new Actor(this);
	AIComponent* aic = new AIComponent(a)

	aic->RegisterState(new AIPatrol(aic));
	aic->RegisterState(new AIDeath(aic));
	aic->RegisterState(new AIAttack(aic));
	
	aic->ChangeState("Patrol");
	*/
}

void Game::unloadData( void ) noexcept
{
	while ( false == _actors.empty() )
	{
		delete _actors.back();
	}

	for ( auto i : _textures )
	{
		SDL_DestroyTexture( i.second );
	}

	_textures.clear();
}

SDL_Texture* Game::getTexture( const std::string& fileName ) noexcept
{
	SDL_Texture* texture = nullptr;

	auto iter = _textures.find( fileName );
	if ( iter != _textures.end() )
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load( fileName.c_str() );
		if ( nullptr == surf)
		{
			SDL_Log( "Failed to load texture file %s", fileName.c_str() );

			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface( _renderer, surf );
		SDL_FreeSurface( surf );
		if ( nullptr == texture)
		{
			SDL_Log( "Failed to convert surface to texture for %s", fileName.c_str() );

			return nullptr;
		}

		_textures.emplace( fileName.c_str(), texture );
	}
	return texture;
}

Grid* Game::getGrid( void ) const noexcept
{
	return _grid;
}

std::vector<Enemy*>& Game::getEnemies( void ) noexcept
{
	return _enemies;
}

Enemy * Game::getNearestEnemy( const Vector2 & position ) const noexcept
{
	Enemy* nearest = nullptr;
	
	if ( 0 < _enemies.size() )
	{
		nearest = _enemies[0];

		float bestDistSq = ( position - _enemies[0]->getPosition() ).LengthSq();
		for ( int ii = 1; ii < static_cast<int>( _enemies.size() ); ++ii )
		{
			float newDistSq = ( position - _enemies[ii]->getPosition() ).LengthSq();
			if ( newDistSq < bestDistSq )
			{
				bestDistSq	= newDistSq;
				nearest		= _enemies[ii];
			}
		}
	}
}

void Game::shutdown( void ) noexcept
{
	unloadData();
	IMG_Quit();
	SDL_DestroyRenderer( _renderer);
	SDL_DestroyWindow( _window );
	SDL_Quit();
}

void Game::addActor( Actor* actor ) noexcept
{
	if (_updatingActors)
	{
		_pendingActors.emplace_back(actor);
	}
	else
	{
		_actors.emplace_back(actor);
	}
}

void Game::removeActor( Actor* actor ) noexcept
{
	auto iter = std::find( _pendingActors.begin(), _pendingActors.end(), actor );
	if ( iter != _pendingActors.end() )
	{
		std::iter_swap( iter, _pendingActors.end() - 1 );
		_pendingActors.pop_back();
	}

	iter = std::find( _actors.begin(), _actors.end(), actor );
	if ( iter != _actors.end() )
	{
		std::iter_swap( iter, _actors.end() - 1 );
		_actors.pop_back();
	}
}

void Game::addSprite( SpriteComponent* sprite ) noexcept
{
	int myDrawOrder = sprite->getDrawOrder();

	auto iter = _sprites.begin();
	for ( ; iter != _sprites.end(); ++iter)
	{
		if ( myDrawOrder < (*iter)->getDrawOrder() )
		{
			break;
		}
	}

	_sprites.insert( iter, sprite );
}

void Game::removeSprite( SpriteComponent* sprite ) noexcept
{
	auto iter = std::find( _sprites.begin(), _sprites.end(), sprite );

	_sprites.erase( iter );
}