#include "SpikeTile.h"
#include "Tile.h"
#include "Constants.h"

namespace GameDev2D
{
	SpikeTile::SpikeTile(unsigned char row, unsigned char col) : Tile(row, col, false)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("spikesHigh");
		m_Tile->SetAnchor(.5, 1.1);
		m_Tile->AttachTo(this);

		CollisionFilter filter(TILE_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		Vector2 offset = Vector2(0.0f, -18.0f);
		AddRectangleCollider(TILE_SIZE -3.0f , 27.0f, offset, filter);
	}
	SpikeTile::~SpikeTile()
	{
		SafeDelete(m_Tile);
	}
	Tile::Type SpikeTile::GetType()
	{
		return Tile::Spikes;
	}
	void SpikeTile::Draw(SpriteBatch * spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}
}