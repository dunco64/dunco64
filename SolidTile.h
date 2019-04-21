#pragma once

#include "Tile.h"
#include <GameDev2D.h>

namespace GameDev2D
{
	class SolidTile : public Tile
	{
	public:
		SolidTile (unsigned char row, unsigned char col);
		~SolidTile();

		Tile::Type GetType() override;
		virtual void Draw(SpriteBatch* spriteBatch) override;

	private:

		SpriteAtlas* m_Tile2;
	};

}