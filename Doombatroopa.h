#pragma once
#include "Constants.h"
#include "Timer.h"
#include "Enemy.h"

namespace GameDev2D
{
	class Doombatroopa : public Enemy
	{
	public:
		Doombatroopa(const Vector2& startingPosition, const Vector2& displacement);
		~Doombatroopa();

		Enemy::Type GetType() override;


		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		float GetWidth() override;
		float GetHeight() override;

	private:

		AnimatedSprite* m_Doombatroopa;
		SpriteAtlas* m_Deadella;
		Timer m_MovementTimer;
		Vector2 m_StartingPosition;
		Vector2 m_Displacement;
	};

}