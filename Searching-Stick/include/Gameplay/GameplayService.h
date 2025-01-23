#pragma once
#include<SFML/System/String.hpp>

namespace Gameplay
{
	class GameplayController;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;
		
		void destroy();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void reset();

	};
}