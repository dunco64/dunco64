#pragma once

#include <GameDev2D.h>
#include "Tile.h"

namespace GameDev2D
{
	class SpikeTile : public Tile
	{
	public:
		SpikeTile(unsigned char row, unsigned char col);
		~SpikeTile();

		Tile::Type GetType() override;
		virtual void Draw(SpriteBatch* spriteBatch) override;

	private:

		SpriteAtlas* m_Tile;
	};
}