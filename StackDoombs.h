#pragma once

#include "Enemy.h"
#include "Timer.h"
namespace GameDev2D
{
	class StackDoombs : public Enemy
	{
	public:
		StackDoombs(const Vector2& startingPosition, const Vector2& displacement);
		~StackDoombs();

		Enemy::Type GetType() override;


		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		float GetWidth() override;
		float GetHeight() override;

		enum State
		{
			Active = 0,
			Dead
		};

		//Sets the state of the Dombella
		void SetState(State state);

		//Returns whether the enemy is dead or not
		bool IsDead();

	private:

		AnimatedSprite* m_StackDoomb;
		SpriteAtlas* m_Deadella;
		SpriteAtlas* m_ActiveSprite;

		Timer m_MovementTimer;
		Vector2 m_StartingPosition;
		Vector2 m_Displacement;
		State m_State;
	};
}