#pragma once
#include <string>

//const std::string LEVEL1_ROOM_FILENAME = "Level1Room1.bin";
//const unsigned char LEVEL1_ROOM1_ROWS = 12;
//const unsigned char LEVEL1_ROOM1_COLS = 8;

const float TILE_SIZE = 64.0f;
const float HALF_TILE_SIZE = 32.0f;

const unsigned short TILE_COLLISION_FILTER = 0x0001;
const unsigned short PLAYER_COLLISION_FILTER = 0x0002;
const unsigned short ENEMY_COLLISION_FILTER = 0x0004;

const float CAMERA_ACCELERATION = 75.0f;
const float CAMERA_DRAG = 0.8f;

const GameDev2D::Vector2 GRAVITY(0.0f, -500.0f);

const float PLAYER_WIDTH = 38.0f;
const float PLAYER_HEIGHT = 42.0f;
const float PLAYER_HALF_WIDTH = 19.0f;
const float PLAYER_HALF_HEIGHT = 21.0f;


const float PLAYER_SPAWN_X[3] = { 92, 92, 92 };
const float PLAYER_SPAWN_Y[3] = { 140.0f, 140.0f, 420.0f};

const float PLAYER_MAX_SPEED = 450.0f;
const float PLAYER_ACCELERATION = 2000.0f;
const float PLAYER_AIR_ACCELERATION_PCT = 0.4f;

const GameDev2D::Vector2 CENTERED_ANCHOR(0.5f, 0.5f);


//const unsigned char LEVEL1_ROOM1[LEVEL1_ROOM1_ROWS][LEVEL1_ROOM1_COLS] =
//{
//	{4,4,4,4,4,4,4,4},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0},
//	{4,4,4,4,4,4,4,4},
//	{4,4,4,4,4,4,4,4},
//	{4,4,4,4,4,4,4,4},
//};

//doombella constants
const float DOOMBA_SPEED = 50.0f;