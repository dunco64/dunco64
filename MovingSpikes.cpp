#include "MovingSpikes.h"
#include "Constants.h"

namespace GameDev2D
{
	MovingSpikes::MovingSpikes(unsigned char row, unsigned char col) : Tile(row, col, false)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("spikesHigh2");
		m_Tile->SetAnchor(.5f, 1.1f);
		m_Tile->SetScaleY(-1.0f);
		m_Tile->AttachTo(this);

		MoveTimer = new Timer(1.0f);
		CollisionFilter filter(TILE_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		Vector2 offset = Vector2(0.0f, 18.0f);
		AddRectangleCollider(TILE_SIZE - 4.0f, 27.0f, offset, filter);
		AddLineCollider(Vector2(0, 0), Vector2(0, -400), filter);

		initialPos = GetPosition();

		m_Acceleration = 0;
		m_Speed = 0;

		izActive = false;
/*
		MoveTimer->Start();*/
		/*if (MoveTimer->IsDone())
		{
			MoveTimer->Restart();
		}*/
	}
	MovingSpikes::~MovingSpikes()
	{
		SafeDelete(m_Tile);
		SafeDelete(MoveTimer);
	}
	Tile::Type MovingSpikes::GetType()
	{
		return Tile::MovingSpikes;
	}
	Sprite * MovingSpikes::GetSprite()
	{
		return m_Tile;
	}

	void MovingSpikes::Update(double delta)
	{

		MoveTimer->Update(delta);
		
		//multiply percentage time complete by distance traveled
		if (izActive == true)
		{
			if (MoveTimer->IsRunning() == false)
			{
			MoveTimer->Start();
			}
			SetPosition(initialPos + Vector2(0, -400)*MoveTimer->GetPercentageComplete());
			if (MoveTimer->IsDone())
			{
				MoveTimer->Stop();
				MoveTimer->Reset();
				//Reset();
				izActive = false;
			}
		}
		


		
		

	}

	void MovingSpikes::Draw(SpriteBatch * spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}


	void MovingSpikes::Reset()
	{
		SetPosition(initialPos);
		izActive = false;
	}

	void MovingSpikes::Activate()
	{
	}

	void MovingSpikes::Deactivate()
	{
	}

	void MovingSpikes::Move()
	{

	}

}

