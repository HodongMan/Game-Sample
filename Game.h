#pragma once

#include "Math.h"

class Ship;
class Actor;
class SpriteComponent;
class Asteroid;
class Grid;
class Enemy;


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

	Grid* getGrid( void ) const noexcept;
	std::vector<Enemy*>& getEnemies( void ) noexcept;
	Enemy* getNearestEnemy( const Vector2& position ) const noexcept;

private:
	void processInput( void ) noexcept;
	void updateGame( void ) noexcept;
	void generateOutput( void ) noexcept;
	void loadData( void ) noexcept;
	void unloadData( void ) noexcept;

	std::unordered_map<std::string, SDL_Texture*> _textures;

	std::vector<Actor*> _actors;
	std::vector<Actor*> _pendingActors;

	std::vector<SpriteComponent*> _sprites;

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	Uint32 _ticksCount;
	bool _isRunning;
	
	bool _updatingActors;

	std::vector<Enemy*> _enemies;
	Grid* _grid;
	float _nextEnemy;
};