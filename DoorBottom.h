#pragma once
#include "Tile.h"	

namespace GameDev2D
{
	class DoorBottom : public Tile
	{
	public:
		DoorBottom(unsigned char row, unsigned char col, bool hasCollider);
		~DoorBottom();

		Tile::Type GetType() override;

		virtual void Draw(SpriteBatch* spriteBatch) override;
	private:

		SpriteAtlas* m_Tile;

	};
}