
#include "EmptyTile.h"

GameDev2D::EmptyTile::EmptyTile(unsigned char row, unsigned char col) : Tile(row, col, false)
{
}

GameDev2D::EmptyTile::~EmptyTile()
{
}

GameDev2D::Tile::Type GameDev2D::EmptyTile::GetType()
{
	return Tile::Type::Empty;
}
