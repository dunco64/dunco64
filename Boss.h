#pragma once

#include "Enemy.h"
#include "Timer.h"

namespace GameDev2D
{
	class Boss : public Enemy
	{
	public:
		Boss (const Vector2& startingPosition, const Vector2& displacement);
		~Boss ();

		Enemy::Type GetType() override;

		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		float GetWidth() override;
		float GetHeight() override;

	private:

		AnimatedSprite* m_Boss;
		Timer m_BossMovementTimer;
		Timer m_MovementDelay;
		Vector2 m_StartingPosition;
		Vector2 m_Displacement;
	};
}