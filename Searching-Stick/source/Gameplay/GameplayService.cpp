#include"../../include/Gameplay/GameplayService.h"
#include"Gameplay/GameplayController.h"
#include"Global/ServiceLocator.h"

namespace Gameplay
{
	using namespace Global;
	class GameplayController;

		GameplayService::GameplayService()
		{
			gameplay_controller = new GameplayController();
			collection_controller = new StickCollectionController();
		}

		GameplayService::~GameplayService()
		{
			destroy();
		}

		void GameplayService::initialize()
		{
			gameplay_controller->initialize();
			collection_controller->initialize();
		}

		void GameplayService::update()
		{
			gameplay_controller->update();
			collection_controller->update();
		}

		void GameplayService::render()
		{
			gameplay_controller->render();
			collection_controller->render();
		}

		void GameplayService::reset()
		{
			gameplay_controller->reset();
			collection_controller->reset();
		}

		void GameplayService::destroy()
		{
			delete gameplay_controller;
		}


	
}