#include "Game.h"
#include "Level.h"
#include <fstream>
#include "Room.h"


namespace GameDev2D
{
	Game::Game() :
		t_MusicTimer(16)
	{
		LoadTexture("Assets");
		float y = 0;
		float x = 0;
		AddGameObject(new Level());

		//Create spritebatch
		m_SpriteBatch = new SpriteBatch();

		//Reset the Game to its default state
		Reset();

		m_Direction = Vector2::Zero;
		m_Accel = Vector2::Zero;

		//Load audio and play music
		//TODO add timer for intro
		LoadAudio("SpaceMusic");
		LoadAudio("Intro");
		m_Music = new Audio("SpaceMusic");
		t_MusicTimer.Start();

		m_Background = new SpriteAtlas("Assets");
		m_Background2 = new SpriteAtlas("Assets");

		m_Background->UseFrame("set4_tiles");
		m_Background2->UseFrame("set4_tiles");

		m_Music->SetDoesLoop(true);
		m_Music->Play();


		//TODO; ASK ABOUT CRAZY AUDIOENGINE.CPP ERROR

		m_Acceleration = 0;


	}

	Game::~Game()
	{
		RemoveAllGameObjects();
		SafeDelete(m_Music);
		//SafeDelete(m_Intro);

		SafeDelete(m_SpriteBatch);

		UnloadTexture("Assets");

		SafeDelete(m_Background);
		SafeDelete(m_Background2);
	}

	void Game::Update(double delta)
	{

		t_MusicTimer.Update(delta);
		//Update ALL the Game Objects
		for (int i = 0; i < GetNumberOfGameObjects(); i++)
		{
			m_GameObjects.at(i)->Update(delta);
		}
	}

	void Game::Draw()
	{
		/*
		m_Background->SetScale(4, 10);
		m_Background->Draw();*/
		m_Background2->SetScale(2.5, 2.5);
		m_Background->SetScale(2.5, 2.5);
		m_Background2->SetPositionY(m_Background->GetHeight() * 2.5);
		m_Background2->Draw();
		m_Background->Draw();
		
		m_SpriteBatch->Begin();
		//Draw ALL the Game Objects
		for (int i = 0; i < GetNumberOfGameObjects(); i++)
		{
			m_GameObjects.at(i)->Draw(m_SpriteBatch);
		}
		m_SpriteBatch->End();
    }

	void Game::Reset()
	{
		//Draw ALL the Game Objects
		for (int i = 0; i < GetNumberOfGameObjects(); i++)
		{
			m_GameObjects.at(i)->Reset();
		}
	}

	GameObject * Game::AddGameObject(GameObject * gameObject)
	{
		if (gameObject != nullptr)
		{
			m_GameObjects.push_back(gameObject);
		}
		return gameObject;
	}

	unsigned int Game::GetNumberOfGameObjects()
	{
		return m_GameObjects.size();
	}

	GameObject * Game::GetGameObjectAtIndex(int index)
	{
		if (index >= 0 && index < GetNumberOfGameObjects())
		{
			return m_GameObjects.at(index);
		}
		return nullptr;
	}

	void Game::RemoveGameObjectAtIndex(int index)
	{
		if (index >= 0 && index < GetNumberOfGameObjects())
		{
			SafeDelete(m_GameObjects.at(index));
			m_GameObjects.erase(m_GameObjects.begin() + index);
		}
	}

	void Game::RemoveAllGameObjects()
	{
		for (int i = 0; i < GetNumberOfGameObjects(); i++)
		{
			SafeDelete(m_GameObjects.at(i));
		}
		m_GameObjects.clear();
	}

	void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
	{

	}

	void Game::HandleRightMouseClick(float aMouseX, float aMouseY)
	{

	}

	void Game::HandleMouseMove(float aMouseX, float aMouseY, float aPreviousX, float aPreviousY)
	{
		
	}

	void Game::HandleKeyPress(Keyboard::Key aKey)
	{

		if (aKey == Keyboard::R)
		{
			Reset();
			
		}
		
	
	}

	void Game::HandleKeyReleased(Keyboard::Key aKey)
	{
	}
	void Game::TimerIsDone(Timer * timer)
	{
		if (timer == &t_MusicTimer)
		{
		//	m_Music->Play();
		}
	}
}