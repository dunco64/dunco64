#pragma once
#include "Timer.h"
#include "Tile.h"	

namespace GameDev2D
{
	class MovingSpikes : public Tile
	{
	public:
		MovingSpikes(unsigned char row, unsigned char col);
		~MovingSpikes();

		Tile::Type GetType() override;

		Sprite* GetSprite() override;

		void Update(double delta) override;
		virtual void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		void Activate() override;
		void Deactivate() override;

		void Move();


		bool izActive;
	protected:


	private:

		SpriteAtlas* m_Tile;
		float m_Acceleration;
		float m_Speed;

		Timer* MoveTimer;


		Vector2 initialPos;
	};
}