#include "Doombella.h"

namespace GameDev2D
{

	Doombella::Doombella(const Vector2 & startingPosition, const Vector2 & displacement):
		m_MovementTimer(4.0)
	{
		m_StartingPosition = startingPosition;
		m_Displacement = displacement;
		m_MovementTimer.SetDuration(m_Displacement.x / DOOMBA_SPEED);

		//Create the animatedsprite
		m_Doombella = new AnimatedSprite("Assets");
		m_Doombella->AddFrame("enemyWalking_1");
		m_Doombella->AddFrame("enemyWalking_2");
		m_Doombella->SetFrameSpeed(12.0f);
		m_Doombella->SetDoesLoop(true);
		m_Doombella->SetAnchor(.5, 0);
		m_Doombella->AttachTo(this);
		
		m_Deadella = new SpriteAtlas("Assets");
		m_Deadella->UseFrame("enemyWalking_4");

		CollisionFilter filter(ENEMY_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		Vector2 offset = Vector2(0.0f, 25.0f);
		AddRectangleCollider(TILE_SIZE * 0.5f, 32.0f, offset,  filter);
	}

	Doombella::~Doombella()
	{
		SafeDelete(m_Doombella);
		SafeDelete(m_Deadella);
	}

	Enemy::Type Doombella::GetType()
	{
		return Enemy::Doombella;
	}

	void Doombella::Update(double delta)
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

	void Doombella::Draw(SpriteBatch * spriteBatch)
	{
		
			spriteBatch->Draw(m_Doombella);
	}

	void Doombella::Reset()
	{
		m_MovementTimer.Restart();
		SetPosition(m_StartingPosition);
		SetScaleY(1.0f);
	}

	float Doombella::GetWidth()
	{
		return m_Doombella->GetWidth();
	}

	float Doombella::GetHeight()
	{
		return m_Doombella->GetHeight();
	}
	void Doombella::SetState(State state)
	{
		if (state != m_State)
		{
			//Set the State
			m_State = state;

			if (m_State == Active)
			{
				m_ActiveSprite = m_Doombella;
			}
			if (m_State == Dead)
			{
				m_ActiveSprite = m_Deadella;
			}
		}
	}
	bool Doombella::IsDead()
	{
		return m_State == Dead;
	}
}