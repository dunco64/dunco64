#include "StackDoombs.h"
#include "Constants.h"

namespace GameDev2D
{
	StackDoombs::StackDoombs(const Vector2 & startingPosition, const Vector2 & displacement) :
		m_MovementTimer(4.0)
	{
		m_StartingPosition = startingPosition;
		m_Displacement = displacement;
		m_MovementTimer.SetDuration(m_Displacement.x / DOOMBA_SPEED);

		//Create the animatedsprite
		m_StackDoomb = new AnimatedSprite("Assets");
		m_StackDoomb->AddFrame("enemyWalking_purp1");
		m_StackDoomb->AddFrame("enemyWalking_purp2");
		m_StackDoomb->SetFrameSpeed(12.0f);
		m_StackDoomb->SetScale(3.0, 3.0);
		m_StackDoomb->SetDoesLoop(true);
		m_StackDoomb->SetAnchor(.5, 0);
		m_StackDoomb->AttachTo(this);

		m_Deadella = new SpriteAtlas("Assets");
		m_Deadella->UseFrame("enemyWalking_4");

		CollisionFilter filter(ENEMY_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		Vector2 offset = Vector2(0.0f, 75.0f);
		AddRectangleCollider(TILE_SIZE * 1.5f,3.0f* 32.0f, offset, filter);
	}

	StackDoombs::~StackDoombs()
	{
		SafeDelete(m_StackDoomb);
		SafeDelete(m_Deadella);
	}

	Enemy::Type StackDoombs::GetType()
	{
		return Enemy::StackDoombs;
	}

	void StackDoombs::Update(double delta)
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

	void StackDoombs::Draw(SpriteBatch * spriteBatch)
	{

		spriteBatch->Draw(m_StackDoomb);
	}

	void StackDoombs::Reset()
	{
		m_MovementTimer.Restart();
		SetPosition(m_StartingPosition);
		SetScaleY(1.0f);
	}

	float StackDoombs::GetWidth()
	{
		return m_StackDoomb->GetWidth();
	}

	float StackDoombs::GetHeight()
	{
		return m_StackDoomb->GetHeight();
	}
	void StackDoombs::SetState(State state)
	{
		if (state != m_State)
		{
			//Set the State
			m_State = state;

			if (m_State == Active)
			{
				m_ActiveSprite = m_StackDoomb;
			}
			if (m_State == Dead)
			{
				m_ActiveSprite = m_Deadella;
			}
		}
	}
	bool StackDoombs::IsDead()
	{
		return m_State == Dead;
	}
}