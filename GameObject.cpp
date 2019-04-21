#include "GameObject.h"

namespace GameDev2D
{
	GameObject::GameObject() : Transformable()
	{
		m_IsActive = true;
		m_SelfDestruct = false;
		m_ShesGonnaBlow = false;
	}

	GameObject::~GameObject()
	{
	}

	bool GameObject::IsAlwaysActive()
	{
		return false;
	}

	void GameObject::SetIsActive(bool isActive)
	{
		m_IsActive = isActive;
	}

	bool GameObject::IsActive()
	{
		return m_IsActive;
	}

	void GameObject::Activate()
	{
		SetIsActive(true);
	}

	void GameObject::Deactivate()
	{
		SetIsActive(false);
	}
	bool GameObject::ShouldSelfDestruct()
	{
		return m_SelfDestruct;
	}
	void GameObject::SelfDestruct()
	{
		m_SelfDestruct = true;
	}
}