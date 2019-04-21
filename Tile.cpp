#include "Tile.h"
#include "Constants.h"

namespace GameDev2D
{
	Tile::Tile(unsigned char row, unsigned char col, bool hasCollider)
	{
		m_Row = row;
		m_Column = col;

		float x = m_Column * TILE_SIZE + TILE_SIZE * 0.5f;
		float y = m_Row * TILE_SIZE + TILE_SIZE * 0.5f;
		SetPosition(x, y);

		if (hasCollider == true)
		{
			CollisionFilter filter(TILE_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
			AddRectangleCollider(TILE_SIZE, TILE_SIZE, filter);
		}
	}

	Tile::~Tile()
	{
	}

	Sprite* Tile::GetSprite()
	{
		return nullptr;
	}

	void Tile::Update(double delta)
	{
	}

	void Tile::Draw(SpriteBatch* spriteBatch)
	{
	}

	void Tile::Reset()
	{
	}

	float Tile::GetWidth()
	{
		return TILE_SIZE;
	}

	float Tile::GetHeight()
	{
		return TILE_SIZE;
	}

	void Tile::SetIsActive(bool IsActive)
	{
		GameObject::SetIsActive(IsActive);

		for (int i = 0; i < GetNumberOfColliders(); i++)
		{
			GetColliderAtIndex(i)->SetIsActive(IsActive);
		}
	}

	unsigned char Tile::GetRow()
	{
		return m_Row;
	}

	unsigned char Tile::GetColumn()
	{
		return m_Column;
	}
}