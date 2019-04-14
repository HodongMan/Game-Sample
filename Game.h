#pragma once

#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Ship;
class Actor;
class SpriteComponent;
class Asteroid;

class Game
{
public:
	Game( void );

	bool initialize( void ) noexcept;
	void runLoop( void ) noexcept;
	void shutdown( void ) noexcept;

	void addActor( Actor* actor ) noexcept;
	void removeActor( Actor* actor ) noexcept;

	void addSprite( SpriteComponent* sprite ) noexcept;
	void removeSprite( SpriteComponent* sprite ) noexcept;

	SDL_Texture* getTexture( const std::string& fileName ) noexcept;

	void addAsteroid( Asteroid* ast) noexcept;
	void removeAsteroid( Asteroid* ast) noexcept;
	std::vector<Asteroid*>& getAsteroids( void ) noexcept { return mAsteroids; }

private:
	void processInput( void ) noexcept;
	void updateGame( void ) noexcept;
	void generateOutput( void ) noexcept;
	void loadData( void ) noexcept;
	void unloadData( void ) noexcept;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<Actor*> mActors;
	
	std::vector<Actor*> mPendingActors;

	std::vector<SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	
	bool mUpdatingActors;

	Ship* mShip;
	std::vector<Asteroid*> mAsteroids;
};