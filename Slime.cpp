#include "Slime.h"
#include "Constants.h"
#include <GameDev2D.h>
namespace GameDev2D
{
	Slime::Slime(unsigned char row, unsigned char col) : Tile(row, col, false)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("Slime");//TODO Add slime texture and logic into room
		m_Tile->SetAnchor(.5, 1.45);
		m_Tile->AttachTo(this);

		CollisionFilter filter(TILE_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		Vector2 offset = Vector2(0.0f, -33.0f);
		AddRectangleCollider(TILE_SIZE, 7, offset, filter);
	}

	Slime::~Slime()
	{
		SafeDelete(m_Tile);
	}

	Tile::Type GameDev2D::Slime::GetType()
	{
		return Tile::Slime;
	}

	void Slime::Draw(SpriteBatch * spriteBatch)
	{
		if (spriteBatch != nullptr)
		{

			spriteBatch->Draw(m_Tile);
		}
		else
		{
			m_Tile->Draw();
		}
	}




}