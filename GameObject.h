#pragma once

#include <GameDev2D.h>

namespace GameDev2D
{
	class SpriteBatch;

	class GameObject : public Transformable
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Update(double delta) = 0;
		virtual void Draw(SpriteBatch* spriteBatch) = 0;
		virtual void Reset() = 0;

		virtual float GetWidth() = 0;
		virtual float GetHeight() = 0;

		virtual bool IsAlwaysActive();

		virtual void SetIsActive(bool isActive);
		virtual bool IsActive();

		virtual void Activate();
		virtual void Deactivate();

		virtual bool ShouldSelfDestruct();
		virtual void SelfDestruct();

		bool m_ShesGonnaBlow;
	protected:
		bool m_IsActive;
		bool m_SelfDestruct;

	};
}