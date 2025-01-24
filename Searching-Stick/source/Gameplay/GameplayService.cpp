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
			initializeRandomSeed();
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

		void GameplayService::initializeRandomSeed()
		{
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
		}

		void GameplayService::searchElement(Collection::SearchType search_type)
		{
			collection_controller->searchElement(search_type);
		}

		Collection::SearchType GameplayService::getCurrentSearchType()
		{
			return collection_controller->getSearchType();
		}

		void GameplayService::reset()
		{
			gameplay_controller->reset();
			collection_controller->reset();
		}

		int GameplayService::getNumberOfComparisons()
		{
			return collection_controller->getNumberOfComparisons();
		}

		int GameplayService::getNumberOfArrayAccess()
		{
			return collection_controller->getNumberOfArrayAccess();
		}

		int GameplayService::getNumberOfSticks()
		{
			return collection_controller->getNumberOfSticks();
		}

		int GameplayService::getDelayMilliseconds()
		{
			return collection_controller->getDelayMilliseconds();
		}

		sf::String GameplayService::getTimeComplexity()
		{
			return collection_controller->getTimeComplexity();
		}

		void GameplayService::destroy()
		{
			delete gameplay_controller;
		}


	
}