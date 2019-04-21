#pragma once

#include <GameDev2D.h>
#include "GameObject.h"
#include "Constants.h"
#include "Timer.h"


namespace GameDev2D
{
	class Level;
	class Tile;
	class MovingSpikes;
	class Enemy;

	class Player : public GameObject, public CollisionCallback, public EventHandler
	{
	public:
		Player(Level* level);
		~Player();

		void Update(double delta) override;
		virtual void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		float GetWidth() override;
		float GetHeight() override;

		//Called from Level whenever the player enters a new Room
		void EnterRoom(const Vector2& spawnPosition);

		//State enum to manage the state of the player
		enum State
		{
			Idle = 0,
			Moving,
			Dead
		};

		//Sets the state of the Player
		void SetState(State state);

		//Returns wether the player is dead or not
		bool IsDead();

		//Handles input events
		void HandleEvent(Event* event) override;

		//Handles collision events between the Ship and the Meteors
		void HandleCollisionEvent(CollisionEvent* collisionEvent) override;

		bool IsColliding(Tile* tile);

	private:
		//Struct to help organize the edge(s) that Player collides with
		enum Edge
		{
			Unknown = 0,
			Left	= 1,
			Right	= 2,
			Top		= 4,
			Bottom	= 8
		};

		//Struct to hold Player specific collision data
		struct CollisionData
		{
			CollisionData()
			{
				pointOfContact = Vector2::Zero;
				edge = 0;
			}

			Vector2 pointOfContact;
			unsigned short edge;
		};

		//Handle collision between a specific Tile and the Player
		void HandleTileCollision(Tile* tile, const CollisionData& collisionData);

		//handle collision between an enemy and the player
		void HandleEnemyCollision(Enemy* enemy, const CollisionData& collisionData);

		//Calculates the single point of contact and the edge (of the player) 
		CollisionData CalculateCollisionData(const std::vector<Vector2> & pointsOfContact);

		//Member variables
		Level* m_Level;
		RectangleCollider* m_Collider;
		SpriteAtlas* m_Idle;
		SpriteAtlas* m_Eye;
		AnimatedSprite* m_Walk;
		Sprite* m_ActiveSprite;
		State m_State;
		Vector2 m_Velocity;
		Vector2 m_Acceleration;
		bool m_IsInAir;
		Tile* m_IgnoreTile;

		Timer* m_DoorTimer;
		Timer* m_DoorTimer2;

		Timer* m_EnemyDeathTimer;

		Timer* m_DeathTimer;

		double AlphaTimer;
		Polygon* m_BigThing;

		SpriteAtlas* m_DeadDoomb;

		bool m_GoomDeath;

		Audio* m_Playerdmg;
		Audio* m_Bounce1;
		Audio* m_Ding;
		Audio* m_Jump;
		Audio* m_EnemyDeath;
	};
}