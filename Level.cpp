#include "Doombella.h"
#include "Doombatroopa.h"
#include "jumpingEnemy.h"
#include "Level.h"
#include "Boss.h"
#include "Gem.h"
#include "StackDoombs.h"
namespace GameDev2D
{
	GameDev2D::Level::Level() :
		m_MovementDelay(2.0),
		m_MovementTimer(4.0)
	{
		y_offset = 0;
		//Add the rooms to the rooms vectors
		Room* room1 = new Room("Level1Room1");
		room1->AddGameObject(new Doombella(Vector2(180, 64), Vector2(192.0f, 0.0f)));
		//room1->AddGameObject(new Doombella(Vector2(180, 130), Vector2(192.0f, 0.0f)));
		//room1->AddGameObject(new Doombatroopa(Vector2(180, 162), Vector2(0.0f, 300.0f)));
		//room1->AddGameObject(new jumpingEnemy(Vector2(200, 182), Vector2(192.0f, y_offset)));
		room1->AddGameObject(new Gem(Vector2(120, 64)));


		m_Rooms.push_back(room1);

		//Room 2 Objects
		Room* room2 = new Room("Level1Room2");
		m_Rooms.push_back(room2);
		////////

		//Room 3 Objects
		Room* room3 = new Room("Level1Room3");

		room3->AddGameObject(new Boss(Vector2(-390, 162), Vector2(11192.0f, 0.0f)));
		room3->AddGameObject(new StackDoombs(Vector2(180, 64), Vector2(11192.0f, 0.0f)));
		room3->AddGameObject(new StackDoombs(Vector2(420, 64), Vector2(11192.0f, 0.0f)));
		
		m_Rooms.push_back(room3);
		///////////

		m_ActiveRoomIndex = 0;


		//Activate room 0
		m_Rooms.at(m_ActiveRoomIndex)->Activate();

		//Create PLayer object
		m_Player = new Player(this);

		//Listen for key down events
		Services::GetInputManager()->GetKeyboard()->AddEventListener(this, KEY_DOWN_EVENT);


	}

	GameDev2D::Level::~Level()
	{
		Services::GetInputManager()->GetKeyboard()->RemoveAllHandlersForListener(this);

		RemoveAllColliders();
		for (int i = 0; i < m_Rooms.size(); i++)
		{
			SafeDelete(m_Rooms.at(i));
		}
		m_Rooms.clear();
		SafeDelete(m_Player);
	}

	void GameDev2D::Level::Update(double delta)
	{
		Vector2 position = GetCamera()->GetPosition();

		if (m_Player->IsDead() == false)
		{
			Vector2 playerPosition = m_Player->GetPosition();
			Vector2 deltaPosition = position - playerPosition;
			if (fabsf(deltaPosition.x) > 1.0f)
			{
				position.x -= deltaPosition.x;
			}
			position.y -= deltaPosition.y;
		}



		//Get the Camera's current position
		Vector2 cameraPosition = GetCamera()->GetPosition();


		//Handle camera movement
		Vector2 playerPosition = m_Player->GetPosition();
		Vector2 deltaPosition = cameraPosition - playerPosition;

		//Only move the Camera if the Player moves more than a single pixel
		if (fabsf(deltaPosition.x) > 1.0f)
		{
			cameraPosition.x -= deltaPosition.x;
		}

		//Clamp the camera's position
		cameraPosition.x = Math::Clamp(cameraPosition.x, GetHalfScreenWidth(), GetActiveRoom()->GetWidth() - GetHalfScreenWidth());
		cameraPosition.y = Math::Clamp(cameraPosition.y, GetHalfScreenHeight(), GetActiveRoom()->GetHeight() - GetHalfScreenHeight());

		GetCamera()->SetPosition(position);

		if (m_Player->IsDead() == true)
		{
			
		}
		//Update the Active Room
		GetActiveRoom()->Update(delta);

		//Update the Player
		m_Player->Update(delta);

		m_MovementDelay.Update(delta);
		m_MovementTimer.Update(delta);

		//Stole movement timer logic from jumpingEnemy
		m_MovementTimer.Start();
		if (m_MovementTimer.IsDone() == true)
		{
			m_MovementDelay.Start();
		
				if (m_MovementDelay.IsDone() == true)
				{
					m_MovementTimer.Restart();
					m_MovementDelay.Reset();
				}
		}

		//set the y-offset variable to the value of the timer's percentage complete
		y_offset = m_MovementTimer.GetPercentageComplete();
		Log::Message(std::to_string(y_offset));
	}



	void GameDev2D::Level::Draw(SpriteBatch* spriteBatch)
	{
		//Draw the active room
		GetActiveRoom()->Draw(spriteBatch);
	
		//draw player
		m_Player->Draw(spriteBatch);

	}

	void GameDev2D::Level::Reset()
	{
		SetActiveRoomIndex(GetActiveRoomIndex());
		GetActiveRoom()->Reset();
		m_Player->Reset();
		
	}

	float Level::GetWidth()
	{
		return GetActiveRoom()->GetWidth();;
	}

	float Level::GetHeight()
	{
		return GetActiveRoom()->GetHeight();
	}

	Room * GameDev2D::Level::GetActiveRoom()
	{
		return m_Rooms.at(m_ActiveRoomIndex);
	}

	unsigned int Level::GetActiveRoomIndex()
	{
		return m_ActiveRoomIndex;
	}

	void Level::SetActiveRoomIndex(unsigned int index)
	{
		if (m_ActiveRoomIndex != index && index < m_Rooms.size())
		{
			//Deactivate the current active room
			GetActiveRoom()->Deactivate();

			//Set the new active room index
			m_ActiveRoomIndex = index;

			//Activate the current active room
			GetActiveRoom()->Activate();

			//Have the player 'enter the room'
			Vector2 position = Vector2(PLAYER_SPAWN_X[m_ActiveRoomIndex], PLAYER_SPAWN_Y[m_ActiveRoomIndex]);
			m_Player->EnterRoom(position);

			//Reset the camera's position
	 		GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());
		}
	}
	void Level::HandleEvent(Event * event)
	{
		if (event->GetEventCode() == KEY_DOWN_EVENT)
		{
			KeyDownEvent* keyDown = (KeyDownEvent*)event;
			if (keyDown->GetKey() == Keyboard::One)
			{
				SetActiveRoomIndex(0);
			}
			else if (keyDown->GetKey() == Keyboard::Two)
			{
				SetActiveRoomIndex(1);
			}
			else if (keyDown->GetKey() == Keyboard::Three)
			{
				SetActiveRoomIndex(2);
			}
		}
	}


}