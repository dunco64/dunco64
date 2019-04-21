#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class Solid1 : public Tile
	{
	public:
		Solid1(unsigned char row, unsigned char col, bool hasCollider);
		~Solid1();

		Tile::Type GetType() override;
		virtual void Draw(SpriteBatch* spriteBatch) override;

	private:

		SpriteAtlas* m_Tile;
	};

}