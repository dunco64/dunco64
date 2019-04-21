#include "SolidTile.h"
#include "Constants.h"
namespace GameDev2D
{
	SolidTile::SolidTile(unsigned char row, unsigned char col) : Tile(row, col, false)
	{
		m_Tile2 = new SpriteAtlas("Assets");
		m_Tile2->UseFrame("RightSlime");
		m_Tile2->SetAnchor(1.45f, .5f);
		m_Tile2->AttachTo(this);

		CollisionFilter filter(TILE_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		Vector2 offset = Vector2(-33.0f,0.0f);
		AddRectangleCollider(7, TILE_SIZE, offset, filter);

	}

	SolidTile::~SolidTile()
	{
		SafeDelete(m_Tile2);
	}

	Tile::Type GameDev2D::SolidTile::GetType()
	{
		return Tile::RightSlime;
	}

	void SolidTile::Draw(SpriteBatch * spriteBatch)
	{
		spriteBatch->Draw(m_Tile2);
	}



}