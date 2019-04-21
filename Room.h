#pragma once

#include "GameObject.h"
#include "Constants.h"
#include "Tile.h"
#include "EmptyTile.h"

namespace GameDev2D
{

	class Level;
	class Tile;

	class Room : public GameObject
	{
	public:
		Room(const std::string& filename);
		virtual ~Room();

		void Update(double delta);
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset();
		unsigned char GetRows();
		unsigned char GetColumns();

		float GetWidth() override;
		float GetHeight() override;

		bool IsOnScreen(GameObject* gameObject);

		bool IsOnScreen(Tile* tile);


		void Activate();
		void Deactivate();

		//GameObject methods
		GameObject* AddGameObject(GameObject* gameObject);
		unsigned int GetNumberOfGameObjects();
		GameObject* GetGameObjectAtIndex(int index);
		void RemoveGameObjectAtIndex(int index);
		void RemoveAllGameObjects();
		
	private:

		GameDev2D::Tile* CreateNewTile(unsigned char data, unsigned char row, unsigned char col);
		
		//Member variables
		Tile*** m_Tiles;

		std::vector<GameObject*> m_GameObjects;

		unsigned char m_NumRows;
		unsigned char m_NumColumns;

		SpriteAtlas* m_UpArrow;
		SpriteAtlas* m_Arrow;
};
}