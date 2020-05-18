#pragma once
#include "Actor.h"


class Game;
class Tile;

class Grid : public Actor
{
public:
	Grid( Game* game );

	void			processClick( const int x, const int y ) noexcept;
	bool			findPath( const Tile* start, const Tile* end ) noexcept;
	void			buildTower( void ) noexcept;

	const Tile*		getStartTile( void ) const noexcept;
	const Tile*		getEndTile( void ) const noexcept;

	void			updateActor( const float deltaTime ) noexcept;

private:

	using TileList = std::vector<Tile*>;

	void			selectTile( const int row, const int col ) noexcept;
	void			updatePathTiles( const Tile* start ) noexcept;

	Tile*			_selectedTile;

	std::vector<TileList> _tiles;

	float _nextEnemy;
};