#include "DoorBottom.h"
#include "Constants.h"
namespace GameDev2D
{
	DoorBottom::DoorBottom(unsigned char row, unsigned char col, bool hasCollider) : Tile(row, col, hasCollider)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("doorRed_top");
		m_Tile->SetAnchor(.5, .5);
		m_Tile->AttachTo(this);

		//CollisionFilter filter(TILE_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		//AddRectangleCollider(TILE_SIZE, TILE_SIZE, filter);
	}
	DoorBottom::~DoorBottom()
	{
		SafeDelete(m_Tile);
	}
	Tile::Type DoorBottom::GetType()
	{
		return Tile::DoorBottom;
	}

	void DoorBottom::Draw(SpriteBatch * spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}


}