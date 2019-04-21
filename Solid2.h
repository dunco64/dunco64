#pragma once

#include "Tile.h"
#include <GameDev2D.h>

namespace GameDev2D
{
	class Solid2 : public Tile 
	{
	public:
		Solid2(unsigned char row, unsigned char col, bool hasCollider);
		~Solid2();

		Tile::Type GetType() override;

		virtual void Draw(SpriteBatch* spriteBatch) override;

	private:

		SpriteAtlas* m_Tile;
	};

}