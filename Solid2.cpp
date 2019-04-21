#include "Solid2.h"
#include <GameDev2D.h>
namespace GameDev2D
{
	Solid2::Solid2(unsigned char row, unsigned char col, bool hasCollider) : Tile(row, col, hasCollider)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("Tile1");
		m_Tile->SetAnchor(.5, .5);
		m_Tile->AttachTo(this);

	}

	Solid2::~Solid2()
	{
		SafeDelete(m_Tile);
	}

	Tile::Type GameDev2D::Solid2::GetType()
	{
		return Tile::Type();
	}

	void Solid2::Draw(SpriteBatch * spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}




}