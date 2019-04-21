#include "Solid1.h"


namespace GameDev2D
{
	Solid1::Solid1(unsigned char row, unsigned char col, bool hasCollider) : Tile(row, col, hasCollider)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("Tile3");
		m_Tile->SetAnchor(.5, .5);
		m_Tile->AttachTo(this);

	}
	Solid1::~Solid1()
	{
		SafeDelete(m_Tile);
	}
	Tile::Type Solid1::GetType()
	{
		return Tile::Solid2;
	}
	void Solid1::Draw(SpriteBatch * spriteBatch)
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