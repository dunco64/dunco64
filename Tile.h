#pragma once

#include "GameObject.h"

namespace GameDev2D
{
	class Tile : public GameObject
	{
	public:
		Tile(unsigned char row, unsigned char col, bool hasCollider);
		virtual ~Tile();

		enum Type
		{
			Empty = 0,
			Collision = 1,
			Slime = 2,
			RightSlime = 4,
			Solid2 = 8,
			Spikes = 16,
			DoorBottom = 32,
			MovingSpikes = 64
			//TODO: ADD MORE TILES

		};
	
	virtual Type GetType() = 0;
	virtual Sprite* GetSprite();
	virtual void Update(double delta) override;
	virtual void Draw(SpriteBatch* spriteBatch) override;
	virtual void Reset() override;

	//override if the derived tile is not 64x64
	virtual float GetWidth() override;
	virtual float GetHeight() override;

	virtual void SetIsActive(bool IsActive) override;

	unsigned char GetRow();
	unsigned char GetColumn();


	private:

	protected:

		unsigned char m_Row;
		unsigned char m_Column;

	};
}