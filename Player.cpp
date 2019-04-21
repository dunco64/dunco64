#include "Player.h"
#include "Level.h"
#include "Room.h"
#include "Tile.h"
#include "MovingSpikes.h"
#include "Enemy.h"

namespace GameDev2D
{
	Player::Player(Level* level)
	{


		m_Level = level;
		LoadTexture("Assets");
		m_Idle = new SpriteAtlas("Assets");
		m_Idle->UseFrame("Idle");
		m_Idle->SetAnchor(.5, .5);
		m_Idle->AttachTo(this);

		m_Walk = new AnimatedSprite("Assets");
		m_Walk->AddFrame("Walk1");
		m_Walk->AddFrame("Walk2");
		m_Walk->SetDoesLoop(true);
		m_Walk->SetAnchor(.5, .5);
		m_Walk->AttachTo(this);

		m_Eye = new SpriteAtlas("Assets");
		m_Eye->UseFrame("Eye");
		m_Eye->SetAnchor(.5, .5);
		m_Eye->SetPositionY(4.0f);
		m_Eye->AttachTo(this);

		m_BigThing = new Polygon(); 
		m_BigThing->MakeRectangle(GetScreenWidth(),GetScreenHeight(), true);
		m_BigThing->SetAnchor(.5, .5);
		m_BigThing->AttachTo(this);


		m_DoorTimer = new Timer(0.7);
		m_DoorTimer2 = new Timer(0.7);
		m_EnemyDeathTimer = new Timer(0.15);
		m_DeathTimer = new Timer(0.7);

		//Load audio files
		LoadAudio("Bounce1");
		LoadAudio("Bounce2");
		LoadAudio("Ding");
		LoadAudio("Hit-Ouch");
		LoadAudio("PUNCH");
		LoadAudio("SPLAT2");
		LoadAudio("Squelch");
		m_Playerdmg = new Audio("Hit-Ouch");
		m_Bounce1 = new Audio("Bounce2");
		m_Ding = new Audio("Ding");
		m_Jump = new Audio("Bounce1");
		m_EnemyDeath = new Audio("PUNCH");


		//m_DeadDoomb = new SpriteAtlas("Assets");
		//m_DeadDoomb->UseFrame("enemyWalking_4");
		//m_DeadDoomb->SetAnchor(.5, 0);

		CollisionFilter filter = CollisionFilter(PLAYER_COLLISION_FILTER, TILE_COLLISION_FILTER | ENEMY_COLLISION_FILTER);
		m_Collider = AddRectangleCollider(PLAYER_WIDTH, PLAYER_HEIGHT, filter, this);

		Services::GetInputManager()->GetKeyboard()->AddEventListener(this, KEY_DOWN_EVENT);
		Services::GetInputManager()->GetKeyboard()->AddEventListener(this, KEY_UP_EVENT);

		AlphaTimer = 0;

		m_BigThing->SetColor(Color::OnyxColor());
		m_BigThing->SetAlpha(0.0f);

		m_GoomDeath = false;

		Reset();
	}
	
	Player::~Player()
	{
		Services::GetInputManager()->GetKeyboard()->RemoveAllHandlersForListener(this);
		SafeDelete(m_Idle);
		SafeDelete(m_Walk);
		SafeDelete(m_Eye);
		SafeDelete(m_BigThing);
		SafeDelete(m_DoorTimer);
		SafeDelete(m_DoorTimer2);
		SafeDelete(m_DeathTimer);
		SafeDelete(m_EnemyDeathTimer);
		SafeDelete(m_Jump);
		SafeDelete(m_EnemyDeath);

		UnloadAudio("Bounce1");
		UnloadAudio("Bounce2");
		UnloadAudio("Ding");
		UnloadAudio("Hit-Ouch");
		UnloadAudio("PUNCH");
		UnloadAudio("SPLAT2");
		UnloadAudio("Squelch");

		SafeDelete(m_Playerdmg);
		SafeDelete(m_Bounce1);
		SafeDelete(m_Ding);
	}

	void Player::Update(double delta)
	{
		if (IsDead() == false)
		{
			float directionX = 0.0f;

			if (IsKeyDown(Keyboard::Left) == true)
			{
				directionX -= 1.0f;
			}
			if (IsKeyDown(Keyboard::Right) == true)
			{
				directionX += 1.0f;
			}

			if (directionX != 0.0f)
			{
				SetScaleX(directionX);
				SetState(Moving);
			}

			Vector2 acceleration = GRAVITY;
			float maxSpeedX = directionX * PLAYER_MAX_SPEED;
			float speedDifferenceX = maxSpeedX - m_Velocity.x;

			if (speedDifferenceX != 0.0f)
			{
				acceleration.x = speedDifferenceX < 0.0f ? -PLAYER_ACCELERATION : PLAYER_ACCELERATION;
				if (m_IsInAir == true)
				{
					acceleration.x *= PLAYER_AIR_ACCELERATION_PCT;
				}
			}

			
			Vector2 velocityIncrement = acceleration * delta;

			if (fabsf(velocityIncrement.x) > fabsf(speedDifferenceX))
			{
				velocityIncrement.x = speedDifferenceX;
			}

			Vector2 previousVelocity = m_Velocity;
			m_Velocity += velocityIncrement;

			if (m_Velocity.y < GRAVITY.y)
			{
				m_Velocity.y = GRAVITY.y;
			}
			Vector2 increment = (previousVelocity + m_Velocity) * delta * 0.5;
			Vector2 position = GetPosition() + increment;

			//Clamp player position
			position.x = Math::Clamp(position.x, PLAYER_HALF_WIDTH, m_Level->GetActiveRoom()->GetWidth());
			position.y = Math::Clamp(position.y, -PLAYER_HALF_HEIGHT, m_Level->GetActiveRoom()->GetHeight());

			if (m_State == Moving)
			{
				float pct = fabsf(m_Velocity.x) / PLAYER_MAX_SPEED;
				float frameSpeed = fmaxf(1.0f, 15.0f * pct);
				m_Walk->SetFrameSpeed(frameSpeed);
				if (fabsf(m_Velocity.x) <= 12.0f || IsKeyDown(Keyboard::Right) == false && IsKeyDown(Keyboard::Left) == false);
				{
					SetState(Idle);
				}
			}

			SetPosition(position);

			//Set this so true, in case the player walks off the edge of a platform
			//If the player doesn't, then they will wollide with the ground
			//and this will be set back to false
			m_IsInAir = true;
		}

		/////////TODO: MOVE FADE TO HUD CLASS AND DRAW IT OVER

		if (m_DoorTimer->IsRunning() == true)
		{
		m_DoorTimer->Update(delta);
		m_BigThing->SetAlpha(m_DoorTimer->GetPercentageComplete());			
		}
		if (m_DoorTimer->IsDone() == true)
		{
			m_DoorTimer2->Update(delta);
			if (m_DoorTimer2->IsRunning() == false)
			{
			//m_DoorTimer2->Start();
			}
			m_BigThing->SetAlpha((m_DoorTimer2->GetPercentageComplete()));
		}

		if (m_DeathTimer->IsRunning() == true)
		{
			m_DeathTimer->Update(delta);
 			m_BigThing->SetAlpha(m_DeathTimer->GetPercentageComplete());

			if (m_DeathTimer->IsDone() == true)
			{
				Reset();
				m_DeathTimer->Reset();

				m_DoorTimer2->Update(delta);
				if (m_DoorTimer2->IsRunning() == false)
				{
					//m_DoorTimer2->Start();
				}
				m_BigThing->SetAlpha((m_DoorTimer2->GetPercentageComplete()));

			}
		}


			m_EnemyDeathTimer->Update(delta);
		//Update enemy's despawn timer
		
			if (m_EnemyDeathTimer->IsDone() == true)
			{
 				m_GoomDeath = true;
				m_EnemyDeathTimer->Reset();
			}
		
		
	}



	void Player::Draw(SpriteBatch* spriteBatch)
	{
		if (IsDead() == false)
		{
			spriteBatch->Draw(m_ActiveSprite);
			spriteBatch->Draw(m_Eye);
		}
		//m_BigThing->SetAlpha(0.0f);
		//m_BigThing->SetColor(Color::OnyxColor()); 
		m_BigThing->Draw();
	}

	void Player::Reset()
	{
		int activeIndex = m_Level->GetActiveRoomIndex();
		Vector2 position = Vector2(PLAYER_SPAWN_X[activeIndex], PLAYER_SPAWN_Y[activeIndex]);
		EnterRoom(position);

		SetState(Idle);
	}

	float Player::GetWidth()
	{
		return m_ActiveSprite->GetWidth();
	}

	float Player::GetHeight()
	{
		return m_ActiveSprite->GetHeight();
	}

	void Player::EnterRoom(const Vector2& spawnPosition)
	{
		SetPosition(spawnPosition);
		m_Velocity = Vector2::Zero;
		m_IsInAir = true;
		SetState(Idle);

		m_IgnoreTile = nullptr;
	}

	void Player::SetState(State state)
	{
		//Ensure the previous state isn't being set, 
		//this prevents unnecessary state change
		if (state != m_State)
		{
			//Set the State
			m_State = state;

			//Idle State
			if (m_State == Idle)
			{
				m_ActiveSprite = m_Idle;
				m_Eye->UseFrame("Eye");
			}
			//Moving State
			if (m_State == Moving)
			{
				m_Walk->SetFrameIndex(0);
				m_ActiveSprite = m_Walk;
				m_Eye->UseFrame("EyeFocused");
			}
			//Dead State
			else if (m_State == Dead)
			{
				//TODO: Handle the player being dead
			}
		}
	}

	bool Player::IsDead()
	{
		return m_State == Dead;
	}

	void Player::HandleEvent(Event * event)
	{
		if (IsDead() == false)
		{
			if (event->GetEventCode() == KEY_DOWN_EVENT)
			{
				KeyDownEvent* keyDown = (KeyDownEvent*)event;
				if (keyDown->GetKey() == Keyboard::Spacebar)
				{
					if (m_IsInAir == false)
					{
						m_Jump->Play();
						m_Velocity.y += 410.0f;
						m_IsInAir = true;
					}
				}
			}
			else if (event->GetEventCode() == KEY_UP_EVENT)
			{
				KeyUpEvent* keyUp = (KeyUpEvent*)event;
				if (keyUp->GetKey() == Keyboard::Spacebar)
				{
					if (m_Velocity.y > 0.0f)
					{
						m_Velocity.y *= 0.5f;
					}
				}
				//TODO: Handle key up input events
			}
		}
	}

	void Player::HandleCollisionEvent(CollisionEvent * collisionEvent)
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
		if (collisionEvent->GetA()->GetFilter().categoryBits == ENEMY_COLLISION_FILTER)
		{
			CollisionData collisionData = CalculateCollisionData(pointsOfContact);
			Enemy* enemy = (Enemy*)collisionEvent->GetA()->GetTransformable();
			HandleEnemyCollision(enemy, collisionData);
		}
		else if (collisionEvent->GetB()->GetFilter().categoryBits == ENEMY_COLLISION_FILTER)
		{
			CollisionData collisionData = CalculateCollisionData(pointsOfContact);
			Enemy* enemy = (Enemy*)collisionEvent->GetB()->GetTransformable();
			HandleEnemyCollision(enemy, collisionData);
		}
	}

	bool Player::IsColliding(Tile * tile)
	{
		std::vector<Vector2> pointsOfContact;

		Collider* playerCollider = GetColliderAtIndex(0);
		Collider* tileCollider = tile->GetNumberOfColliders() > 0 ? tile->GetColliderAtIndex(0) : nullptr;

		if (tileCollider != nullptr)
		{
			std::vector<Vector2> pointofContact;
			return Services::GetCollisionManager()->CheckCollision(playerCollider, tileCollider, pointsOfContact);
		}
		return false;
	}

	void Player::HandleTileCollision(Tile* tile, const CollisionData& collisionData)
	{
		//Don't handle collision if the edge is unknown:
		if (collisionData.edge == Unknown)
		{
			return;
		}

		if (tile == m_IgnoreTile)
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

		//die noob
		if (type == Tile::Spikes)
		{

			if ((collisionData.edge & Bottom) == Bottom)
			{
				//Vector2 pos = Vector2(PLAYER_SPAWN_X[0], PLAYER_SPAWN_Y[0]);
				//GetCamera()->Translate(pos);
				if (m_DeathTimer->IsRunning() == false)
				{
					m_Playerdmg->Play();
				}
				m_DeathTimer->Start();
				m_Velocity.x = 0;
				m_Velocity.y = 0;
				SetState(Dead);
				//GetCamera()->Shake(2, 0.5);
				//if (m_DeathTimer->IsDone())
				//{
				//m_DeathTimer->Reset();
				//Reset();
				//}

			}
		}
		//Moving thwomp spikes
		if (type == Tile::MovingSpikes)
		{
			if ((collisionData.edge & Top) == Top)
			{
				if (m_DeathTimer->IsRunning() == false)
				{
					m_Playerdmg->Play();
				}
				m_DeathTimer->Start();
				m_Velocity.x = 0;
				m_Velocity.y = 0;

				SetState(Dead);
				//GetCamera()->Shake(2, 0.5);
				//if (m_DeathTimer->IsDone())
				//{
				//	m_DeathTimer->Reset();
				//	Reset();
				//}
			}
			if ((collisionData.edge & Left) == Left || (collisionData.edge & Right) == Right )
			{
				static_cast<MovingSpikes*>(tile)->izActive = true;
			}
		}
		//when you touch a slime, you bounce up
		if (type == Tile::Slime)
		{
				{
					m_Velocity.y = 0;
					m_Velocity.y += 550.0f;
					m_IsInAir = true;
					m_Bounce1->Play();
				 }
		}
		
		//when you touch right slime, bounce right
		if (type == Tile::RightSlime)
		{
			if ((collisionData.edge & Left) == Left)
			{
					m_Velocity.y = 0;
					m_Velocity.y += 400.0f;
					m_Velocity.x = 0;
					m_Velocity.x += 1000.0f;
					m_IsInAir = true;
					m_Bounce1->Play();

			}
		}

		//Make sure that wheny ou press up on a door, you go through
		if (type == Tile::DoorBottom)
		{
			if (IsKeyDown(Keyboard::Up) == true)
			{
				m_DoorTimer->Start();
				m_Velocity.x = 0;
				m_Velocity.y = 0;
				m_Ding->Play();
				//GetCamera()->Shake(2, 0.5);

			}
				if (m_DoorTimer->IsDone())
				{
					Reset();
					m_DoorTimer->Reset();
					m_Level->SetActiveRoomIndex(m_Level->GetActiveRoomIndex() + 1);
				}
		}
	}

	void Player::HandleEnemyCollision(Enemy * enemy, const CollisionData & collisionData)
	{
		Enemy::Type type = enemy->GetType();

		if (type == Enemy::Doombatroopa || type == Enemy::Doombella || type == Enemy::jumpingEnemy)
		{
			if ((collisionData.edge & Bottom) == Bottom)
			{
				m_ShesGonnaBlow = true;
				m_EnemyDeathTimer->Start();

				//if (m_GoomDeath == true)
				{
					enemy->SelfDestruct();
				}

				//when the player touches the enemy, bounce up 
				m_Velocity.y = 0;
				m_Velocity.y += 300.0f;
				m_IsInAir = true;
				m_EnemyDeath->Play();
			}
			if ((collisionData.edge & Left) == Left || (collisionData.edge & Right) == Right)
			{
				if (m_DeathTimer->IsRunning() == false)
				{
					m_Playerdmg->Play();
				}
				m_DeathTimer->Start();
				m_Velocity.x = 0;
				m_Velocity.y = 0;

				SetState(Dead);
			}
		}
		if (type == Enemy::Boss)
			if ((collisionData.edge & Bottom) == Bottom)
			{
				//when the player touches the enemy, bounce up 
				m_Velocity.y = 0;
				m_Velocity.y += 300.0f;
				m_IsInAir = true;

			}
		if ((collisionData.edge & Left) == Left || (collisionData.edge & Right) == Right)
		{
			m_DeathTimer->Start();
			m_Velocity.x = 0;
			m_Velocity.y = 0;
			SetState(Dead);

			if (m_DeathTimer->IsRunning() == false)
			{
				m_Playerdmg->Play();
			}
		}
		if (type == Enemy::StackDoombs)
		{
			m_Velocity.y = 0;
			m_Velocity.y += 450.0f;
			m_IsInAir = true;
			m_Bounce1->Play();

		}
	}

	Player::CollisionData Player::CalculateCollisionData(const std::vector<Vector2> & pointsOfContact)
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

							if (Math::IsClosest(relativePointsOfContact.at(0).x, relativePointsOfContact.at(1).x, m_Idle->GetWidth() * 0.5f) == relativePointsOfContact.at(0).x)
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

							if (Math::IsClosest(relativePointsOfContact.at(0).x, relativePointsOfContact.at(1).x, -m_Idle->GetWidth() * 0.5f) == relativePointsOfContact.at(0).x)
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
							if (Math::IsClosest(relativePointsOfContact.at(0).y, relativePointsOfContact.at(1).y, m_Idle->GetHeight() * 0.5f) == relativePointsOfContact.at(0).y)
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
							if (Math::IsClosest(relativePointsOfContact.at(0).y, relativePointsOfContact.at(1).y, -m_Idle->GetHeight() * 0.5f) == relativePointsOfContact.at(0).y)
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