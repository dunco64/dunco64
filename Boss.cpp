#include "Boss.h"
#include "Constants.h"
namespace GameDev2D
{
	Boss::Boss(const Vector2 & startingPosition, const Vector2 & displacement) :
		m_MovementDelay(2.0),
		m_BossMovementTimer(4.0)
	{
		m_StartingPosition = startingPosition;
		m_Displacement = displacement;
		m_BossMovementTimer.SetDuration(m_Displacement.x / DOOMBA_SPEED);

		m_Boss = new AnimatedSprite("Assets");
		m_Boss->AddFrame("Boss_Head");
		m_Boss->AddFrame("Boss_Head_Blink");
		m_Boss->AddFrame("Boss_Head");
		m_Boss->AddFrame("Boss_Head_Mouth");
		m_Boss->SetFrameSpeed(0.4);
		m_Boss->SetDoesLoop(true);
		m_Boss->SetScale(3, 3);
		m_Boss->SetAnchor(CENTERED_ANCHOR);
		//m_Boss->SetScale(0.5f,0.5f);
		m_Boss->AttachTo(this);

		
		CollisionFilter filter(ENEMY_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		/*Vector2 offset = Vector2(0.0f, 25.0f);*/
		AddRectangleCollider(m_Boss->GetWidth(), m_Boss->GetHeight() ,/* offset, */filter);
	}

	Boss::~Boss()
	{
		SafeDelete(m_Boss);
	}

	Enemy::Type Boss::GetType()
	{
		return Enemy::Boss;
	}

	void Boss::Update(double delta)
	{
		

		m_BossMovementTimer.Start();

		m_BossMovementTimer.Update(delta);
		
		if (GetScale().x == 1.0f)
		{
			Vector2 displacement = m_Displacement * m_BossMovementTimer.GetPercentageComplete();
			SetPosition(m_StartingPosition + displacement);

			if (m_BossMovementTimer.IsDone() == true)
			{
				SetScaleX(-1.0f);
				m_BossMovementTimer.Restart();
			}
		}
		else if (GetScale().x == -1.0f)
		{
			Vector2 displacement = m_Displacement * (1.0f - m_BossMovementTimer.GetPercentageComplete());
			SetPosition(m_StartingPosition + displacement);

			if (m_BossMovementTimer.IsDone() == true)
			{
				SetScaleX(1.0f);
				m_BossMovementTimer.Restart();
			}
		}
	}

	void Boss::Draw(SpriteBatch * spriteBatch)
	{
		if (spriteBatch != nullptr)
		{
			spriteBatch->Draw(m_Boss);
		}
		else
		{
			m_Boss->Draw();
		}
	}

	void Boss::Reset()
	{
		m_BossMovementTimer.Restart();
		SetPosition(m_StartingPosition);
		SetScaleY(1.0f);
	}

	float Boss::GetWidth()
	{
		return m_Boss->GetWidth();
	}

	float Boss::GetHeight()
	{
		return m_Boss->GetHeight();
	}
}