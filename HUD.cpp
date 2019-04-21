#include "HUD.h"	
#include "Level.h"

namespace GameDev2D
{
	HUD::HUD(Level * level)
	{
		m_Level = level;

		m_BigThing = new Polygon(); 
		m_BigThing->MakeRectangle(GetScreenWidth(),GetScreenHeight(), true);
		m_BigThing->SetAnchor(.5, .5);
		m_BigThing->AttachTo(this);

		m_BigThing->SetColor(Color::OnyxColor());
		m_BigThing->SetAlpha(0.0f);
	}
	HUD::~HUD()
	{

		SafeDelete(m_BigThing);
	}
	void HUD::Update(double delta)
	{
	}
	void HUD::Draw()
	{
	}
}