#include "Background.h"

namespace GameDev2D
{
	Background::Background()
	{
		LoadTexture("Assets");
		m_Background = new SpriteAtlas("Assets");
		m_Background2 = new SpriteAtlas("Assets");

		m_Background->UseFrame("set3_background");
		m_Background2->UseFrame("set4_tiles");

	}
	Background::~Background()
	{
		SafeDelete(m_Background);
		SafeDelete(m_Background2);
	}
	void Background::Draw(SpriteBatch* spriteBatch)
	{
		m_Background->Draw();
		m_Background2->Draw();
	}
	void Background::Update(double delta)
	{
		
	}
}