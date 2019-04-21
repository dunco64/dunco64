#pragma once

#include "GameObject.h"
#include "Constants.h"
namespace GameDev2D
{
	class Gem : public GameObject
	{
	public:
		Gem(const Vector2& startingPosition);
		~Gem();

		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		float GetWidth() override;
		float GetHeight() override;
	private:

		SpriteAtlas* m_Gem;

		Vector2 m_StartingPosition;
	};

}