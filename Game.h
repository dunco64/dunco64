#pragma once

#include <GameDev2D.h>
#include "GameObject.h"
#include "Constants.h"
#include "Timer.h"

namespace GameDev2D
{
	//Class definition
	class Game 
	{
	public:
		Game();  //Constructor
		~Game(); //Destructor

		//Write game logic in the Update method
		void Update(double delta);

		//Render game objects in the Draw method
		void Draw();

		//Resets the Game
		void Reset();

		//GameObject methods
		GameObject* AddGameObject(GameObject* gameObject);
		unsigned int GetNumberOfGameObjects();
		GameObject* GetGameObjectAtIndex(int index);
		void RemoveGameObjectAtIndex(int index);
		void RemoveAllGameObjects();

		//Input methods
		void HandleLeftMouseClick(float mouseX, float mouseY);
		void HandleRightMouseClick(float mouseX, float mouseY);
		void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
		void HandleKeyPress(Keyboard::Key key);
		void HandleKeyReleased(Keyboard::Key key);


		void TimerIsDone(Timer* timer);

	private:
		//Member variables GO HERE 
		std::vector<GameObject*> m_GameObjects;
		SpriteBatch* m_SpriteBatch;

		float y;
		float x;

		Vector2 m_Direction;
		Vector2 m_Accel;

		float m_Acceleration;

		Audio* m_Music;
		//Audio* m_Intro;

		Timer t_MusicTimer;



		SpriteAtlas* m_Background;
		SpriteAtlas* m_Background2;
	};
}
