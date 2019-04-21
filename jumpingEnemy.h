#pragma once
#include "Tile.h"
#include "Enemy.h"
#include "Timer.h"

namespace GameDev2D
{

	class jumpingEnemy : public Enemy, public CollisionCallback, public EventHandler	
	{
	public:
		jumpingEnemy(const Vector2& startingPosition, const Vector2& displacement);
		~jumpingEnemy();

		Enemy::Type GetType() override;


		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		float GetWidth() override;
		float GetHeight() override;

		//Handles collision events between the Ship and the Meteors
		void HandleCollisionEvent(CollisionEvent* collisionEvent) override;

		bool IsColliding(Tile* tile);

		float y_offset;
	private:

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


		//Calculates the single point of contact and the edge (of the player) 
		CollisionData CalculateCollisionData(const std::vector<Vector2> & pointsOfContact);

		//Struct to help organize the edge(s) that Player collides with
		enum Edge
		{
			Unknown = 0,
			Left = 1,
			Right = 2,
			Top = 4,
			Bottom = 8
		};

		AnimatedSprite* m_jumpingEnemy;
		Timer m_MovementTimer;
		Timer m_MovementDelay;
		Vector2 m_StartingPosition;
		Vector2 m_Displacement;


		Vector2 m_Velocity;
		Vector2 m_Acceleration;
		bool m_IsInAir;
	};





}//closing namespace