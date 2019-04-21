#pragma once
#include "Tile.h"
#include <GameDev2D.h>

namespace GameDev2D
{
	class Slime : public Tile
	{
	public:
		Slime(unsigned char row, unsigned char col);
		~Slime();

		Tile::Type GetType() override;
		virtual void Draw(SpriteBatch* spriteBatch) override;

	private:

		SpriteAtlas* m_Tile;
	};

}