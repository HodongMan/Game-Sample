#include "Game.h"

Game::Game() noexcept
	: mWindow( nullptr )
	, mRenderer( nullptr )
	, mTicksCount( 0 )
	, mIsRunning( false )
	, mPaddleDir( 0 )
{

}

bool Game::Initialize() noexcept
{
	int sdlResult = SDL_Init( SDL_INIT_VIDEO );
	if ( 0 != sdlResult )
	{
		SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if ( false == mWindow )
	{
		SDL_Log( "Failed to create window: %s", SDL_GetError() );
		return false;
	}

	SDL_Delay(3000);
	
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	
	if ( false == mRenderer )
	{
		SDL_Log( "Failed to create renderer: %s", SDL_GetError() );
		return false;
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

	return true;
}

void Game::MainLoop() noexcept
{
	while ( true == mIsRunning )
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() noexcept
{
	SDL_Event event;

	while ( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState( nullptr );

	if (state[SDL_SCANCODE_ESCAPE] )
	{
		mIsRunning = false;
	}

	mPaddleDir = 0;

	if (state[SDL_SCANCODE_W] )
	{
		mPaddleDir -= 1;
	}

	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame() noexcept
{
	while ( false == SDL_TICKS_PASSED( SDL_GetTicks(), mTicksCount + 16 ) )
	{

	}

	float deltaTime = ( SDL_GetTicks() - mTicksCount ) / 1000.0f;

	if ( deltaTime > 0.5f )
	{
		deltaTime = 0.05f;
	}

	mTicksCount = SDL_GetTicks();

	if ( 0 != mPaddleDir )
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		if ( mPaddlePos.y < ( paddleH/2.0f + thickness ) )
		{
			mPaddlePos.y = paddleH/2.0f + thickness;
		}
		else if ( mPaddlePos.y > ( 768.0f - paddleH/2.0f - thickness ) )
		{
			mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
		}
	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	float diff = mPaddlePos.y - mBallPos.y;

	diff = ( diff > 0.0f ) ? diff : -diff;

	if ( ( diff <= paddleH / 2.0f ) &&
		 ( mBallPos.x <= 25.0f ) && 
		 ( mBallPos.x >= 20.0f ) &&
		 ( mBallVel.x < 0.0f ) )
	{
		mBallVel.x *= -1.0f;
	}
	else if ( mBallPos.x <= 0.0f )
	{
		mIsRunning = false;
	}
	else if ( mBallPos.x >= ( 1024.0f - thickness ) && ( mBallVel.x > 0.0f ) )
	{
		mBallVel.x *= -1.0f;
	}

	if ( mBallPos.y <= thickness && mBallVel.y < 0.0f )
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if ( mBallPos.y >= (768 - thickness) &&
		( mBallVel.y > 0.0f ) )
	{
		mBallVel.y *= -1;
	}

}

void Game::GenerateOutput() noexcept
{
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);

	SDL_RenderClear( mRenderer );

	SDL_SetRenderDrawColor( mRenderer, 255, 255, 255, 255 );

	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};

	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// Draw ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::ShutDown() noexcept
{
	SDL_DestroyRenderer( mRenderer );
	SDL_DestroyWindow( mWindow );
	SDL_Quit();
}