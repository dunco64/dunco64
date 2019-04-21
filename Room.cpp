#include "Room.h"
#include <fstream>
#include "SolidTile.h"
#include "Solid2.h"
#include "EmptyTile.h"
#include "SpikeTile.h"
#include "DoorBottom.h"
#include "MovingSpikes.h"
#include "Slime.h"
#include "Solid1.h"

namespace GameDev2D
{

	GameDev2D::Room::Room(const std::string & filename)
	{
		m_Tiles = nullptr;
		m_NumRows = 0;
		m_NumColumns = 0;

		unsigned char** tiles = nullptr;
		std::string path = Services::GetApplication()->GetPathForResourceInDirectory(filename, "bin", "Data"); //TODO : Add bin file to directory
		std::ifstream input;
		input.open(path, std::ios::in | std::ios::binary);

		//Did the File open?
		if (input.is_open() == true)
		{
			//Read how many rows and colums there are
			input.read((char*)&m_NumRows, sizeof(unsigned char));
			input.read((char*)&m_NumColumns, sizeof(unsigned char));

			tiles = new unsigned char*[m_NumRows];

			for (unsigned char r = 0; r < m_NumRows; r++)
			{
				tiles[r] = new unsigned char[m_NumColumns];

				size_t bytes = sizeof(unsigned char) * m_NumColumns;
				input.read((char*)tiles[r], bytes);
			}

			//Close the ifstream
			input.close();

			//it's a sign
			m_UpArrow = new SpriteAtlas("Assets");
			m_UpArrow->UseFrame("signArrow_up");
			m_Arrow = new SpriteAtlas("Assets");
			m_Arrow->UseFrame("signArrow_TR");

		}
		if (m_NumRows > 0 && m_NumColumns > 0)
		{
			//Allocate the array of Tile* arrays
			m_Tiles = new Tile**[m_NumRows];

			//Loop through and create the Tiles
			for (unsigned char r = 0; r < m_NumRows; r++)
			{
				m_Tiles[r] = new Tile*[m_NumColumns];

				for (unsigned char c = 0; c < m_NumColumns; c++)
				{
					m_Tiles[r][c] = CreateNewTile(tiles[r][c], r, c);
				}
			}
		}

		//Delete the temp files arraw
		if (tiles != nullptr)
		{
			for (unsigned char r = 0; r < m_NumRows; r++)
			{				
					SafeDeleteArray(tiles[r]);				
			}
			SafeDeleteArray(tiles);

		}

		Deactivate();

		Reset();
	}

	GameDev2D::Room::~Room()
	{

		for (unsigned char r = 0; r < m_NumRows; r++)
		{
			for (unsigned char c = 0; c < m_NumColumns; c++)
			{
				SafeDelete(m_Tiles[r][c]);
			}
			SafeDeleteArray(m_Tiles[r]);
		}
		SafeDeleteArray(m_Tiles);

		SafeDelete(m_UpArrow);
		SafeDelete(m_Arrow);

		RemoveAllGameObjects();
	}

	void GameDev2D::Room::Update(double delta)
	{
		for (unsigned char r = 0; r < m_NumRows; r++)
		{
			for (unsigned char c = 0; c < m_NumColumns; c++)
			{
				if (IsOnScreen(m_Tiles[r][c]) == true)
				{
					m_Tiles[r][c]->SetIsActive(true);
					m_Tiles[r][c]->Update(delta);
					}
				else 
				{
					m_Tiles[r][c]->SetIsActive(false);
				}
			}
		}

		//notify the game objects that they are Reset
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			if (IsOnScreen(m_GameObjects.at(i)) == true)
			{
				m_GameObjects.at(i)->SetIsActive(true);
			m_GameObjects.at(i)->Update(delta);
			}
			else
			{
				m_GameObjects.at(i)->SetIsActive(false);
			}
		}

		//Check for game objects the self destructed
		std::vector<GameObject*>::iterator it = m_GameObjects.begin();
		while (it != m_GameObjects.end())
		{
			if ((*it)->ShouldSelfDestruct() == true)
			{
				SafeDelete((*it));
				it = m_GameObjects.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void GameDev2D::Room::Draw(SpriteBatch* spriteBatch)
	{
		m_Arrow->SetPosition(406, 75);
		m_Arrow->Draw();
		m_UpArrow->SetPosition(848.0f, 256.0f);
		m_UpArrow->Draw();

		//int startingRow = (GetCamera()->GetPosition().y - GetHalfScreenHeight()) / TILE_SIZE;
		//int startingCol = (GetCamera()->GetPosition().x - GetHalfScreenWidth()) / TILE_SIZE;


		//TODO: fix fade
		for (unsigned char r = 0; r < m_NumRows; r++)
		{
			for (unsigned char c = 0; c < m_NumColumns; c++)
			{
				if (m_Tiles[r][c]->IsActive() == true && m_Tiles[r][c]->GetType() != Tile::Empty)
				{
				m_Tiles[r][c]->Draw(spriteBatch);
				}
			}
		}
		
	
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			if (m_GameObjects.at(i)->IsActive() == true)
			{

			m_GameObjects.at(i)->Draw(spriteBatch);
			}
		}
		

	}

	void GameDev2D::Room::Reset()
	{
		for (unsigned char r = 0; r < m_NumRows; r++)
		{
			for (unsigned char c = 0; c < m_NumColumns; c++)
			{
				m_Tiles[r][c]->Reset();
			}
		}
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			m_GameObjects.at(i)->Reset();
		}
	}

	unsigned char GameDev2D::Room::GetRows()
	{
		return m_NumRows;
	}

	unsigned char GameDev2D::Room::GetColumns()
	{
		return m_NumColumns;
	}

	float GameDev2D::Room::GetWidth()
	{
		return (float)GetColumns() * TILE_SIZE;
	}

	float GameDev2D::Room::GetHeight()
	{
		return (float)GetRows() * TILE_SIZE;
	}

	bool Room::IsOnScreen(GameObject * gameObject)
	{
		//if (gameObject->IsAlwaysActive() == true)
		//{
		//	return true;
		//}

		Vector2 cameraPosition = GetCamera()->GetPosition();
		float left = cameraPosition.x - GetHalfScreenWidth() - gameObject->GetWidth();
		float right = cameraPosition.x + GetHalfScreenWidth() + gameObject->GetWidth();
		float top = cameraPosition.y + GetHalfScreenHeight() + gameObject->GetHeight();
		float bottom = cameraPosition.y - GetHalfScreenHeight() - gameObject->GetHeight();

		Vector2 position = gameObject->GetPosition();
		return  position.x >= left
			&&  position.x <= right
			&&  position.y >= bottom
			&&  position.y <= top;
	}

	bool Room::IsOnScreen(Tile * tile)
	{
		Vector2 cameraPosition = GetCamera()->GetPosition();
		float left = cameraPosition.x - GetHalfScreenWidth() - HALF_TILE_SIZE;
		float right = cameraPosition.x + GetHalfScreenWidth() + HALF_TILE_SIZE;
		float top = cameraPosition.y + GetHalfScreenHeight() + HALF_TILE_SIZE;
		float bottom = cameraPosition.y - GetHalfScreenHeight() - HALF_TILE_SIZE;
		
		Vector2 tilePosition = tile->GetPosition();
		return  tilePosition.x >= left
			&& tilePosition.x <= right
			&& tilePosition.y >= bottom
			&& tilePosition.y <= top;
	}

	void Room::Activate()
	{
		for (unsigned char r = 0; r < GetRows(); r++)
		{
			for (unsigned char c = 0; c < GetColumns(); c++)
			{
				Tile* tile = m_Tiles[r][c];
				tile->SetIsActive(IsOnScreen(tile));
			}
		}
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			m_GameObjects.at(i)->Activate();
		}
	}

	void Room::Deactivate()
	{
		for (unsigned char r = 0; r < GetRows(); r++)
		{
			for (unsigned char c = 0; c < GetColumns(); c++)
			{
				Tile* tile = m_Tiles[r][c];
				tile->SetIsActive(false);
			}
		}
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			m_GameObjects.at(i)->Deactivate();
		}
	}

	GameObject * Room::AddGameObject(GameObject * gameObject)
	{
		if (gameObject != nullptr)
		{
			m_GameObjects.push_back(gameObject);
		}
		return gameObject;
	}

	unsigned int Room::GetNumberOfGameObjects()
	{
		return m_GameObjects.size();
	}

	GameObject * Room::GetGameObjectAtIndex(int index)
	{
		if (index >= 0 && index < GetNumberOfGameObjects())
		{
			return m_GameObjects.at(index);
		}
		return nullptr;
	}

	void Room::RemoveGameObjectAtIndex(int index)
	{
		if (index >= 0 && index < GetNumberOfGameObjects())
		{
			SafeDelete(m_GameObjects.at(index));
			m_GameObjects.erase(m_GameObjects.begin() + index);
		}
	}

	void Room::RemoveAllGameObjects()
	{
		for (int i = 0; i < GetNumberOfGameObjects(); i++)
		{
			SafeDelete(m_GameObjects.at(i));
		}
		m_GameObjects.clear();
	}

	GameDev2D::Tile * GameDev2D::Room::CreateNewTile(unsigned char data, unsigned char row, unsigned char col)
	{
		bool hasCollider = (data & 1) == 1; //collider
		bool hasVariant = (data & 2) == 2; // variant

		if (hasVariant == true)
		{
			return new Slime(row, col);
		}
		else
		{
			if ((data & Tile::RightSlime) == Tile::RightSlime)
			{
				return new SolidTile(row, col);
			}
			if ((data & Tile::Solid2) == Tile::Solid2)
			{
				return new Solid1(row, col, hasCollider);
			}
			if ((data & Tile::Spikes) == Tile::Spikes)
			{
				return new SpikeTile(row, col);
			}
			if ((data & Tile::DoorBottom) == Tile::DoorBottom)
			{
				return new DoorBottom(row, col, hasCollider);
			}
			if ((data & Tile::MovingSpikes) == Tile::MovingSpikes)
			{
				return new MovingSpikes(row, col);
			}
		}

			return new EmptyTile(row, col);
		//Add more logic here to create additional Tile objects

	}
}