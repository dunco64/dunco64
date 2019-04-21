#include "Constants.h"
#include "jumpingEnemy.h"

namespace GameDev2D
{

	jumpingEnemy::jumpingEnemy(const Vector2 & startingPosition, const Vector2 & displacement) :
		m_MovementTimer(4.0),
		m_MovementDelay(2.0)
	{
		m_StartingPosition = startingPosition;
		m_Displacement = displacement;
		m_MovementTimer.SetDuration(m_Displacement.x / DOOMBA_SPEED);

		//Create the animatedsprite
		m_jumpingEnemy = new AnimatedSprite("Assets");

		m_jumpingEnemy->AddFrame("playerBlue_up3");
		m_jumpingEnemy->AddFrame("playerBlue_up2");
		m_jumpingEnemy->AddFrame("playerBlue_up1");
		m_jumpingEnemy->AddFrame("playerBlue_up2");
		m_jumpingEnemy->AddFrame("playerBlue_up3");

		m_jumpingEnemy->SetFrameSpeed(10.0f);
		m_jumpingEnemy->SetDoesLoop(true);
		m_jumpingEnemy->SetAnchor(.5, 0);
		m_jumpingEnemy->AttachTo(this);


		CollisionFilter filter(ENEMY_COLLISION_FILTER, PLAYER_COLLISION_FILTER | TILE_COLLISION_FILTER);
		Vector2 offset = Vector2(0.0f, 25.0f);
		AddRectangleCollider(TILE_SIZE * 0.5f, 32.0f, offset, filter);

		y_offset = 0;
	}

	jumpingEnemy::~jumpingEnemy()
	{
		SafeDelete(m_jumpingEnemy);
	}

	Enemy::Type jumpingEnemy::GetType()
	{
		return Enemy::jumpingEnemy;
	}

	void jumpingEnemy::Update(double delta)
	{

		m_MovementDelay.Update(delta);
		m_MovementTimer.Update(delta);

		if (GetScale().x == 1.0f)
		{
			Vector2 displacement = m_Displacement * m_MovementTimer.GetPercentageComplete();
			SetPosition(m_StartingPosition + displacement);

			if (m_MovementTimer.IsDone() == true)
			{
				m_MovementDelay.Start();
				if (m_MovementTimer.IsRunning() == false)
				{
					m_jumpingEnemy->Stop();
			/*	m_jumpingEnemy->SetDoesLoop(false);*/
					if (m_MovementDelay.IsDone() == true)
					{			
					//m_jumpingEnemy->SetDoesLoop(true);
						m_jumpingEnemy->Play();

					SetScaleX(-1.0f);
					m_MovementTimer.Restart();
					m_MovementDelay.Reset();
					}
				}

			}
		}
		else if (GetScale().x == -1.0f)
		{
			Vector2 displacement = m_Displacement * (1.0f - m_MovementTimer.GetPercentageComplete());
			SetPosition(m_StartingPosition + displacement);

			if (m_MovementTimer.IsDone() == true)
			{
				m_MovementDelay.Start();
				m_jumpingEnemy->Stop();

				if (m_MovementTimer.IsRunning() == false)
				{
					if (m_MovementDelay.IsDone() == true)
					{
				SetScaleX(1.0f);
						m_MovementTimer.Restart();
						m_jumpingEnemy->Play();
						m_MovementDelay.Reset();

					}
				}
			}
		}

		y_offset = m_MovementTimer.GetPercentageComplete();


		//if (m_MovementTimer.IsDone() == true && m_MovementDelay.IsRunning() == true)
		//{
		//}
		//if (m_MovementTimer.IsRunning() == true)
		//{

		//}

		//////////////////////////////////////////////////START OF COLLISION BULLSHIT

//			float directionX = 0.0f;
//
//			if (IsKeyDown(Keyboard::Left) == true)
//			{
//				directionX -= 1.0f;
//			}
//			if (IsKeyDown(Keyboard::Right) == true)
//			{
//				directionX += 1.0f;
//			}
//
//			if (directionX != 0.0f)
//			{
//				SetScaleX(directionX);
//				/*SetState(Moving);*/
//			}
//
//			Vector2 acceleration = GRAVITY;
//			float maxSpeedX = directionX * PLAYER_MAX_SPEED;
//			float speedDifferenceX = maxSpeedX - m_Velocity.x;
//
//			if (speedDifferenceX != 0.0f)
//			{
//				acceleration.x = speedDifferenceX < 0.0f ? -PLAYER_ACCELERATION : PLAYER_ACCELERATION;
//				if (m_IsInAir == true)
//				{
//					acceleration.x *= PLAYER_AIR_ACCELERATION_PCT;
//				}
//			}
//
//			
//			Vector2 velocityIncrement = acceleration * delta;
//
//			if (fabsf(velocityIncrement.x) > fabsf(speedDifferenceX))
//			{
//				velocityIncrement.x = speedDifferenceX;
//			}
//
//			Vector2 previousVelocity = m_Velocity;
//			m_Velocity += velocityIncrement;
//
//			if (m_Velocity.y < GRAVITY.y)
//			{
//				m_Velocity.y = GRAVITY.y;
//			}
//			Vector2 increment = (previousVelocity + m_Velocity) * delta * 0.5;
//			Vector2 position = GetPosition() + increment;
//
//			//Clamp player position
//			/*position.x = Math::Clamp(position.x, PLAYER_HALF_WIDTH, m_Level->GetActiveRoom()->GetWidth());
//			position.y = Math::Clamp(position.y, -PLAYER_HALF_HEIGHT, m_Level->GetActiveRoom()->GetHeight());
//*/
//			//if (m_State == Moving)
//			//{
//				//float pct = fabsf(m_Velocity.x) / PLAYER_MAX_SPEED;
//				//float frameSpeed = fmaxf(1.0f, 15.0f * pct);
//				//m_Walk->SetFrameSpeed(frameSpeed);
//				//if (fabsf(m_Velocity.x) <= 12.0f || IsKeyDown(Keyboard::Right) == false && IsKeyDown(Keyboard::Left) == false);
//				//{
//				//	SetState(Idle);
//				//}
//			//}
//
//			SetPosition(position);
//
//			//Set this so true, in case the player walks off the edge of a platform
//			//If the player doesn't, then they will wollide with the ground
//			//and this will be set back to false
//			m_IsInAir = true;
//		



	}

	void jumpingEnemy::Draw(SpriteBatch * spriteBatch)
	{

		
			spriteBatch->Draw(m_jumpingEnemy);
		

	}

	void jumpingEnemy::Reset()
	{
		m_MovementTimer.Restart();
		SetPosition(m_StartingPosition);
		SetScaleY(1.0f);
	}

	float jumpingEnemy::GetWidth()
	{
		return m_jumpingEnemy->GetWidth();
	}

	float jumpingEnemy::GetHeight()
	{
		return m_jumpingEnemy->GetHeight();
	}

	void jumpingEnemy::HandleCollisionEvent(CollisionEvent * collisionEvent)
	{
		std::vector<Vector2> pointsOfContact;
		for (int i = 0; i < collisionEvent->GetNumberOfPointsOfContact(); i++)
		{
			pointsOfContact.push_back(collisionEvent->GetPointOfContact(i));
		}

		if (collisionEvent->GetA()->GetFilter().categoryBits == TILE_COLLISION_FILTER)
		{
			CollisionData collisionData = CalculateCollisionData(pointsOfContact);
			Tile* tile = (Tile*)collisionEvent->GetA()->GetTransformable();
			HandleTileCollision(tile, collisionData);
		}
		else if (collisionEvent->GetB()->GetFilter().categoryBits == TILE_COLLISION_FILTER)
		{
			CollisionData collisionData = CalculateCollisionData(pointsOfContact);
			Tile* tile = (Tile*)collisionEvent->GetB()->GetTransformable();
			HandleTileCollision(tile, collisionData);
		}
	
	}

	bool jumpingEnemy::IsColliding(Tile * tile)
	{
		std::vector<Vector2> pointsOfContact;

		Collider* enemyCollider = GetColliderAtIndex(0);
		Collider* tileCollider = tile->GetNumberOfColliders() > 0 ? tile->GetColliderAtIndex(0) : nullptr;

		if (tileCollider != nullptr)
		{
			std::vector<Vector2> pointofContact;
			return Services::GetCollisionManager()->CheckCollision(enemyCollider, tileCollider, pointsOfContact);
		}
		return false;
	}

	void jumpingEnemy::HandleTileCollision(Tile* tile, const CollisionData& collisionData)
	{
		//Don't handle collision if the edge is unknown:
		if (collisionData.edge == Unknown)
		{
			return;
		}



		//Get the Tile's Type
		Tile::Type type = tile->GetType();


		//Handle the tles that can't be passed through
		if (type == Tile::Solid2 || type == Tile::Spikes || type == Tile::MovingSpikes)
		{
			if ((collisionData.edge & Bottom) == Bottom)
			{
				SetPositionY(collisionData.pointOfContact.y + PLAYER_HALF_HEIGHT);
				m_Velocity.y = 0.0f;
				m_IsInAir = false;
			}
		}
		if (type == Tile::Solid2 || type == Tile::Spikes)
		{
			if ((collisionData.edge & Top) == Top)
			{
				SetPositionY(collisionData.pointOfContact.y - PLAYER_HALF_HEIGHT);
				m_Velocity.y = 0.0f;
			}
			if ((collisionData.edge & Right) == Right)
			{
				SetPositionX(collisionData.pointOfContact.x - PLAYER_HALF_WIDTH);
				m_Velocity.x = 0.0f;
			}
			if ((collisionData.edge & Left) == Left)
			{
				SetPositionX(collisionData.pointOfContact.x + PLAYER_HALF_WIDTH);
				m_Velocity.x = 0.0f;
			}
		}
	}

	jumpingEnemy::CollisionData jumpingEnemy::CalculateCollisionData(const std::vector<Vector2> & pointsOfContact)
	{
		CollisionData collisionData;

		//Build the vector for the relative (to the player) points of contact
		std::vector<Vector2> relativePointsOfContact;
		for (int i = 0; i < pointsOfContact.size(); i++)
		{
			relativePointsOfContact.push_back(pointsOfContact.at(i) - GetPosition());
		}

		//Handle collision where the is only 2 points of contact
		if (pointsOfContact.size() == 2)
		{
			//Bottom collision
			if (relativePointsOfContact.at(0).y == relativePointsOfContact.at(1).y && relativePointsOfContact.at(0).y < 0.0f)
			{
				collisionData.edge |= Bottom;
				collisionData.pointOfContact = Vector2((pointsOfContact.at(0).x + pointsOfContact.at(1).x) * 0.5f, pointsOfContact.at(0).y);
			}
			//Top collision
			else if (relativePointsOfContact.at(0).y == relativePointsOfContact.at(1).y && relativePointsOfContact.at(0).y > 0.0f)
			{
				collisionData.edge |= Top;
				collisionData.pointOfContact = Vector2((pointsOfContact.at(0).x + pointsOfContact.at(1).x) * 0.5f, pointsOfContact.at(0).y);
			}
			//Right collision
			else if (relativePointsOfContact.at(0).x == relativePointsOfContact.at(1).x && relativePointsOfContact.at(0).x > 0.0f)
			{
				collisionData.edge |= Right;
				collisionData.pointOfContact = Vector2(pointsOfContact.at(0).x, (pointsOfContact.at(0).y + pointsOfContact.at(1).y) * 0.5f);
			}
			//Left collision
			else if (relativePointsOfContact.at(0).x == relativePointsOfContact.at(1).x && relativePointsOfContact.at(0).x < 0.0f)
			{
				collisionData.edge |= Left;
				collisionData.pointOfContact = Vector2(pointsOfContact.at(0).x, (pointsOfContact.at(0).y + pointsOfContact.at(1).y) * 0.5f);
			}
			else
			{
				float dx = relativePointsOfContact.at(0).x - relativePointsOfContact.at(1).x;
				float dy = relativePointsOfContact.at(0).y - relativePointsOfContact.at(1).y;

				if (fabsf(dx) < 0.5f && fabsf(dy) < 0.5f)
				{
					//Discard
				}
				else
				{
					if (fabsf(dx) < fabsf(dy))
					{
						//Right collision
						if (relativePointsOfContact.at(0).x > 0.0f && relativePointsOfContact.at(1).x > 0.0f)
						{
							collisionData.edge |= Right;

							if (Math::IsClosest(relativePointsOfContact.at(0).x, relativePointsOfContact.at(1).x, m_jumpingEnemy->GetWidth() * 0.5f) == relativePointsOfContact.at(0).x)
							{
								collisionData.pointOfContact = pointsOfContact.at(1);
							}
							else
							{
								collisionData.pointOfContact = pointsOfContact.at(0);
							}
						}
						//Left collision
						else if (relativePointsOfContact.at(0).x < 0.0f && relativePointsOfContact.at(1).x < 0.0f)
						{
							collisionData.edge |= Left;

							if (Math::IsClosest(relativePointsOfContact.at(0).x, relativePointsOfContact.at(1).x, -m_jumpingEnemy->GetWidth() * 0.5f) == relativePointsOfContact.at(0).x)
							{
								collisionData.pointOfContact = pointsOfContact.at(1);
							}
							else
							{
								collisionData.pointOfContact = pointsOfContact.at(0);
							}
						}
						else
						{
							//Discard
						}
					}
					else if (fabsf(dy) < fabsf(dx))
					{
						//Top collision
						if (relativePointsOfContact.at(0).y > 0.0f && relativePointsOfContact.at(1).y > 0.0f)
						{
							collisionData.edge |= Top;
							if (Math::IsClosest(relativePointsOfContact.at(0).y, relativePointsOfContact.at(1).y, m_jumpingEnemy->GetHeight() * 0.5f) == relativePointsOfContact.at(0).y)
							{
								collisionData.pointOfContact = pointsOfContact.at(1);
							}
							else
							{
								collisionData.pointOfContact = pointsOfContact.at(0);
							}
						}
						//Bottom collision
						else if (relativePointsOfContact.at(0).y < 0.0f && relativePointsOfContact.at(1).y < 0.0f)
						{
							collisionData.edge |= Bottom;
							if (Math::IsClosest(relativePointsOfContact.at(0).y, relativePointsOfContact.at(1).y, -m_jumpingEnemy->GetHeight() * 0.5f) == relativePointsOfContact.at(0).y)
							{
								collisionData.pointOfContact = pointsOfContact.at(1);
							}
							else
							{
								collisionData.pointOfContact = pointsOfContact.at(0);
							}
						}
						else
						{
							//Discard
						}
					}
				}
			}
		}
		//Handle collision where the is 3 points of contact
		else if (pointsOfContact.size() == 3)
		{
			//Bottom collision
			if (relativePointsOfContact.at(0).y == relativePointsOfContact.at(1).y && relativePointsOfContact.at(0).y <= 0.0f
				|| relativePointsOfContact.at(0).y == relativePointsOfContact.at(2).y && relativePointsOfContact.at(0).y <= 0.0f
				|| relativePointsOfContact.at(1).y == relativePointsOfContact.at(2).y && relativePointsOfContact.at(1).y <= 0.0f)
			{
				collisionData.edge |= Bottom;
				collisionData.pointOfContact.y = Math::AreSame(pointsOfContact.at(0).y, pointsOfContact.at(1).y, pointsOfContact.at(2).y);
			}

			//Top collision
			if (relativePointsOfContact.at(0).y == relativePointsOfContact.at(1).y && relativePointsOfContact.at(0).y > 0.0f
				|| relativePointsOfContact.at(0).y == relativePointsOfContact.at(2).y && relativePointsOfContact.at(0).y > 0.0f
				|| relativePointsOfContact.at(1).y == relativePointsOfContact.at(2).y && relativePointsOfContact.at(1).y > 0.0f)
			{
				collisionData.edge |= Top;
				collisionData.pointOfContact.y = Math::AreSame(pointsOfContact.at(0).y, pointsOfContact.at(1).y, pointsOfContact.at(2).y);
			}

			//Right collision
			if (relativePointsOfContact.at(0).x == relativePointsOfContact.at(1).x && relativePointsOfContact.at(0).x > 0.0f
				|| relativePointsOfContact.at(0).x == relativePointsOfContact.at(2).x && relativePointsOfContact.at(0).x > 0.0f
				|| relativePointsOfContact.at(1).x == relativePointsOfContact.at(2).x && relativePointsOfContact.at(1).x > 0.0f)
			{
				collisionData.edge |= Right;
				collisionData.pointOfContact.x = Math::AreSame(pointsOfContact.at(0).x, pointsOfContact.at(1).x, pointsOfContact.at(2).x);
			}

			//Left collision
			if (relativePointsOfContact.at(0).x == relativePointsOfContact.at(1).x && relativePointsOfContact.at(0).x < 0.0f
				|| relativePointsOfContact.at(0).x == relativePointsOfContact.at(2).x && relativePointsOfContact.at(0).x < 0.0f
				|| relativePointsOfContact.at(1).x == relativePointsOfContact.at(2).x && relativePointsOfContact.at(1).x < 0.0f)
			{
				collisionData.edge |= Left;
				collisionData.pointOfContact.x = Math::AreSame(pointsOfContact.at(0).x, pointsOfContact.at(1).x, pointsOfContact.at(2).x);
			}
		}

		return collisionData;
	}

}