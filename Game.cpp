
#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"


Game::Game( void )
	: mWindow( nullptr )
	, mRenderer( nullptr )
	, mIsRunning( true )
	, mUpdatingActors( false )
{

}

bool Game::initialize( void )
{
	if ( 0 != SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) )
	{
		SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );

		return false;
	}
	
	mWindow = SDL_CreateWindow( "Test", 100, 100, 1024, 768, 0 );
	if ( nullptr == mWindow )
	{
		SDL_Log( "Failed to create window: %s", SDL_GetError() );

		return false;
	}

	mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( nullptr == mRenderer )
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

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::runLoop( void ) noexcept
{
	while ( true == mIsRunning )
	{
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::processInput( void ) noexcept
{
	SDL_Event event;
	while ( true == SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState( nullptr );
	if ( true == keyState[SDL_SCANCODE_ESCAPE] )
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;

	for ( auto actor : mActors )
	{
		actor->processInput( keyState );
	}

	mUpdatingActors = false;
}

void Game::updateGame( void ) noexcept
{
	while ( false == SDL_TICKS_PASSED( SDL_GetTicks(), mTicksCount + 16 ) )
		;

	float deltaTime = ( SDL_GetTicks() - mTicksCount ) / 1000.0f;
	if ( 0.05f < deltaTime )
	{
		deltaTime = 0.05f;
	}

	mTicksCount = SDL_GetTicks();

	mUpdatingActors = true;
	
	for ( auto actor : mActors )
	{
		actor->update( deltaTime );
	}

	mUpdatingActors = false;

	for ( auto pending : mPendingActors )
	{
		mActors.emplace_back( pending );
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for ( auto actor : mActors )
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
	SDL_SetRenderDrawColor( mRenderer, 0, 0, 0, 255 );
	SDL_RenderClear( mRenderer );

	for ( auto sprite : mSprites )
	{
		sprite->draw( mRenderer );
	}

	SDL_RenderPresent( mRenderer );
}

void Game::loadData( void ) noexcept
{
	mShip = new Ship( this );
	mShip->setPosition( Vector2( 100.0f, 384.0f ) );
	mShip->setScale( 1.5f );

	Actor* temp = new Actor( this );
	temp->setPosition( Vector2( 512.0f, 384.0f ) );


	const int numAsteroids = 20;

	for ( int i = 0; i < numAsteroids; ++i )
	{
		new Asteroid( this );
	}

}

void Game::unloadData( void ) noexcept
{
	while ( false == mActors.empty() )
	{
		delete mActors.back();
	}

	for ( auto i : mTextures )
	{
		SDL_DestroyTexture( i.second );
	}

	mTextures.clear();
}

SDL_Texture* Game::getTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;

	auto iter = mTextures.find( fileName );
	if ( iter != mTextures.end() )
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load( fileName.c_str() );
		if ( nullptr == surf)
		{
			SDL_Log( "Failed to load texture file %s", fileName.c_str() );

			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface( mRenderer, surf );
		SDL_FreeSurface( surf );
		if ( nullptr == tex)
		{
			SDL_Log( "Failed to convert surface to texture for %s", fileName.c_str() );

			return nullptr;
		}

		mTextures.emplace( fileName.c_str(), tex );
	}
	return tex;
}

void Game::addAsteroid( Asteroid* ast ) noexcept
{
	mAsteroids.emplace_back( ast );
}

void Game::removeAsteroid( Asteroid* ast ) noexcept
{
	auto iter = std::find( mAsteroids.begin(), mAsteroids.end(), ast );
	if ( iter != mAsteroids.end() )
	{
		mAsteroids.erase( iter );
	}
}

void Game::shutdown( void ) noexcept
{
	unloadData();
	IMG_Quit();
	SDL_DestroyRenderer( mRenderer);
	SDL_DestroyWindow( mWindow );
	SDL_Quit();
}

void Game::addActor( Actor* actor ) noexcept
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::removeActor( Actor* actor ) noexcept
{
	auto iter = std::find( mPendingActors.begin(), mPendingActors.end(), actor );
	if ( iter != mPendingActors.end() )
	{
		std::iter_swap( iter, mPendingActors.end() - 1 );
		mPendingActors.pop_back();
	}

	iter = std::find( mActors.begin(), mActors.end(), actor );
	if ( iter != mActors.end() )
	{
		std::iter_swap( iter, mActors.end() - 1 );
		mActors.pop_back();
	}
}

void Game::addSprite( SpriteComponent* sprite ) noexcept
{
	int myDrawOrder = sprite->getDrawOrder();

	auto iter = mSprites.begin();
	for ( ; iter != mSprites.end(); ++iter)
	{
		if ( myDrawOrder < (*iter)->getDrawOrder() )
		{
			break;
		}
	}

	mSprites.insert( iter, sprite );
}

void Game::removeSprite( SpriteComponent* sprite ) noexcept
{
	auto iter = std::find( mSprites.begin(), mSprites.end(), sprite );

	mSprites.erase( iter );
}