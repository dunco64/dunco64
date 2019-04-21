#include "Doombatroopa.h"

namespace GameDev2D
{
	
	Doombatroopa::Doombatroopa(const Vector2 & startingPosition, const Vector2 & displacement): m_MovementTimer(4.0)
	{
		m_StartingPosition = startingPosition;
		m_Displacement = displacement;
		m_MovementTimer.SetDuration(m_Displacement.y / DOOMBA_SPEED);

		//Create the animatedsprite
		m_Doombatroopa = new AnimatedSprite("Assets");
		m_Doombatroopa->AddFrame("enemyWalking_2");
		m_Doombatroopa->AddFrame("enemyWalking_3");
		m_Doombatroopa->SetFrameSpeed(3.0f);
		m_Doombatroopa->SetDoesLoop(true);
		m_Doombatroopa->SetAnchor(.5, 0);
		m_Doombatroopa->AttachTo(this);

		m_Deadella = new SpriteAtlas("Assets");
		m_Deadella->UseFrame("enemyWalking_4");

		CollisionFilter filter(ENEMY_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		Vector2 offset = Vector2(0.0f, 25.0f);
		AddRectangleCollider(TILE_SIZE * 0.5f, 32.0f, offset, filter);
	}
	Doombatroopa::~Doombatroopa()
	{
		SafeDelete(m_Doombatroopa);
		SafeDelete(m_Deadella);
	}
	Enemy::Type Doombatroopa::GetType()
	{
		return Enemy::Doombatroopa;
	}
	void Doombatroopa::Update(double delta)
	{


		m_MovementTimer.Update(delta);

		if (GetScale().x == 1.0f)
		{
			Vector2 displacement = m_Displacement * m_MovementTimer.GetPercentageComplete();
			SetPosition(m_StartingPosition + displacement);

			if (m_MovementTimer.IsDone() == true)
			{
				SetScaleX(-1.0f);
				m_MovementTimer.Restart();
			}
		}
		else if (GetScale().x == -1.0f)
		{
			Vector2 displacement = m_Displacement * (1.0f - m_MovementTimer.GetPercentageComplete());
			SetPosition(m_StartingPosition + displacement);

			if (m_MovementTimer.IsDone() == true)
			{
				SetScaleX(1.0f);
				m_MovementTimer.Restart();
			}
		}
	}
	void Doombatroopa::Draw(SpriteBatch * spriteBatch)
	{
		spriteBatch->Draw(m_Doombatroopa);
	}
	void Doombatroopa::Reset()
	{
		m_MovementTimer.Restart();
		SetPosition(m_StartingPosition);
		SetScaleY(1.0f);
	}
	float Doombatroopa::GetWidth()
	{
		return m_Doombatroopa->GetWidth();
	}
	float Doombatroopa::GetHeight()
	{
		return m_Doombatroopa->GetHeight();
	}
}