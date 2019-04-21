#pragma once
#include "GameObject.h"

namespace GameDev2D
{
	class Background : public GameObject
	{
	public:
		Background();
		virtual ~Background();

		virtual void Draw(SpriteBatch* spriteBatch) override;
		virtual void Update(double delta) override;

	private:

		SpriteAtlas* m_Background;

		SpriteAtlas* m_Background2;
	};

}