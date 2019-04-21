#pragma once

#include "GameObject.h"
#include "Room.h"
#include "Player.h"
#include "Doombella.h"
#include "Timer.h"

namespace GameDev2D
{
	class Player;
	class Level : public GameObject, public EventHandler
	{
	public:
		Level();
		virtual ~Level();

		void Update(double delta);
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset();

		float GetWidth() override;
		float GetHeight() override;

		Room* GetActiveRoom();

		unsigned int GetActiveRoomIndex();
		void SetActiveRoomIndex(unsigned int index);
		
		void HandleEvent(Event* event) override;


		unsigned int m_ActiveRoomIndex;

	protected:
		Room* m_Room;
		Room* room1;
		Room* room2;
		Room* room3;

		Player* m_Player;

		Timer m_MovementTimer;
		Timer m_MovementDelay;

		std::vector<Room*> m_Rooms;

		float y_offset;
	};
}