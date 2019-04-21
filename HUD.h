#pragma once

#include <GameDev2D.h>

namespace GameDev2D
{
	class Level;

	class HUD : public Transformable
	{
	public:
		HUD(Level* level);
		~HUD();

		void Update(double delta);
		void Draw();
	private:

		Polygon* m_FadeOverlay;
		Level* m_Level;
		
		Polygon* m_BigThing;
	};

	
}