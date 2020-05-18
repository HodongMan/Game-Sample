#include "pch.h"

#include "Grid.h"
#include "TypeGrid.h"
#include "Enemy.h"

Grid::Grid( Game * game )
	: Actor( game )
	, _selectedTile( nullptr ) 
	, _nextEnemy( 0.0f )
{
	_tiles.clear();
	_tiles.resize( NUMROWS );

	for ( int ii = 0; ii < static_cast<int>( _tiles.size() ); ++ii )
	{
		_tiles[ii].resize( NUMCOLS );
	}

	for ( int ii = 0; ii < NUMROWS; ++ii )
	{
		for ( int jj = 0; jj < NUMCOLS; ++jj )
		{
			_tiles[ii][jj] = new Tile( getGame() );
			_tiles[ii][jj]->setPosition( Vector2( TILESIZE / 2.0f + jj * TILESIZE, STARTY + ii * TILESIZE ) );
		}
	}

	for ( int ii = 0; ii < NUMROWS; ++ii )
	{
		for ( int jj = 0; jj < NUMCOLS; ++jj )
		{
			if ( 0 < ii )
			{
				_tiles[ii][jj]->_adjacent.push_back( _tiles[ii-1][jj] );
			}
			if ( ii < NUMROWS - 1)
			{
				_tiles[ii][jj]->_adjacent.push_back( _tiles[ii+1][jj] );
			}
			if ( 0 < jj )
			{
				_tiles[ii][jj]->_adjacent.push_back( _tiles[ii][jj-1] );
			}
			if ( jj < NUMCOLS - 1 )
			{
				_tiles[ii][jj]->_adjacent.push_back( _tiles[ii][jj+1] );
			}
		}
	}

	getStartTile()->setTileState( Tile::EStart );
	getEndTile()->setTileState( Tile::EBase );

	findPath( getEndTile(), getStartTile() );
	updatePathTiles( getStartTile() );

	_nextEnemy = ENEMYTIME;
}

void Grid::processClick( const int x, const int y ) noexcept
{
	int newY = y - static_cast<int>( ( STARTY - TILESIZE ) / 2);
	if ( 0 <= newY )
	{
		int newX = x / static_cast<int>( TILESIZE );
		newY /= static_cast<int>( TILESIZE );
		if ( ( 0 <= newX) &&
			 ( newX < static_cast<int>( NUMCOLS ) ) &&
			 ( 0 <= newY ) &&
			 ( newY < static_cast<int>( NUMROWS ) ) )
		{
			selectTile( newY, newX );
		}
	}
}

bool Grid::findPath( const Tile* start, const Tile* end ) noexcept
{
	return false;
}

void Grid::buildTower( void ) noexcept
{

}

const Tile* Grid::getStartTile( void ) const noexcept
{
	return _tiles[3][0];
}

const Tile * Grid::getEndTile( void ) const noexcept
{
	return _tiles[3][15];
}

void Grid::updateActor( const float deltaTime ) noexcept
{
	Actor::updateActor(deltaTime);

	_nextEnemy -= deltaTime;
	if ( _nextEnemy <= 0.0f)
	{
		new Enemy( getGame() );
		_nextEnemy += ENEMYTIME;
	}
}

void Grid::selectTile( const int row, const int col ) noexcept
{
	Tile::TileState tstate = _tiles[row][col]->getTileState();
	if ( ( Tile::EStart != tstate ) && ( Tile::EBase != tstate  ) )
	{
		if ( nullptr != _selectedTile )
		{
			_selectedTile->ToggleSelect();
		}
		_selectedTile = _tiles[row][col];
		_selectedTile->ToggleSelect();
	}
}

void Grid::updatePathTiles( const Tile* start ) noexcept
{

}
