#include "Gem.h"

namespace GameDev2D
{
	Gem::Gem(const Vector2 & startingPosition)
	{
		LoadTexture("Assets");
		m_StartingPosition = startingPosition;

		m_Gem = new SpriteAtlas("Assets");
		m_Gem->UseFrame("yellowCrystal");
		m_Gem->SetAnchor(.5, 0);
		m_Gem->AttachTo(this);

		//TODO add collider
	}
	Gem::~Gem()
	{
		SafeDelete(m_Gem);
	}
	void Gem::Update(double delta)
	{
	}
	void Gem::Draw(SpriteBatch * spriteBatch)
	{
		spriteBatch->Draw(m_Gem);
	}
	void Gem::Reset()
	{
		SetPosition(m_StartingPosition);
	}
	float Gem::GetWidth()
	{
		return m_Gem->GetWidth();
	}
	float Gem::GetHeight()
	{
		return m_Gem->GetHeight();
	}
}