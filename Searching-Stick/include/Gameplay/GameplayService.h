#pragma once
#include<SFML/System/String.hpp>
#include"Gameplay/StickCollection/StickCollectionModel.h"
#include"Gameplay/StickCollection/StickCollectionController.h"

namespace Gameplay
{
	using namespace Collection;
	class GameplayCntroller;
	enum class SearchType;

	class GameplayController;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;
		StickCollectionController* collection_controller;
		
		void destroy();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void reset();

		void searchElement(Collection::SearchType search_type);

		Collection::SearchType getCurrentSearchType();

		int getNumberOfSticks();
	};
}