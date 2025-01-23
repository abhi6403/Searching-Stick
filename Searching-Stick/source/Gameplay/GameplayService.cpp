#include"../../include/Gameplay/GameplayService.h"
#include"Gameplay/GameplayController.h"

namespace Gameplay
{
	class GameplayController;

		GameplayService::GameplayService()
		{
			gameplay_controller = new GameplayController();
		}

		GameplayService::~GameplayService()
		{
			destroy();
		}

		void GameplayService::initialize()
		{
			gameplay_controller->initialize();
		}

		void GameplayService::update()
		{
			gameplay_controller->update();
		}

		void GameplayService::render()
		{
			gameplay_controller->render();
		}

		void GameplayService::reset()
		{
			gameplay_controller->reset();
		}

		void GameplayService::destroy()
		{
			delete gameplay_controller;
		}


	
}