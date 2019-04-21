#pragma once
#include "GameObject.h"

namespace GameDev2D
{
	class Enemy : public GameObject
	{
	public:
		Enemy();
		virtual ~Enemy();

		enum Type
		{
			Doombella = 0,
			Doombatroopa = 1,
			jumpingEnemy = 2,
			Boss = 3,
			StackDoombs
			//Add more enemy types here
		};

		virtual Type GetType() = 0;

		virtual void Update(double delta) = 0;
		virtual void Draw(SpriteBatch* spriteBatch) = 0;
		virtual void Reset() = 0;

		virtual float GetWidth() = 0;
		virtual float GetHeight() = 0;
	private:

	};


}