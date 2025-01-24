#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<thread>

namespace Gameplay
{
	namespace Collection
	{
		class StickCollectionModel;
		class StickCollectionView;
		enum class SearchType;
		struct Stick;

		class StickCollectionController
		{

		private:
			int number_of_comparisons;
			int number_of_array_access;
			int current_operation_delay;

			sf::String time_complexity;

			StickCollectionView* collection_view;
			StickCollectionModel* collection_model;

			std::vector<Stick*>sticks;

			Stick* stick_to_search;

			Collection::SearchType search_type;
			std::thread search_thread;

			void initializeSticks();
			void shuffleSticks();
			float calculateStickWidth();

			void updateSticksPosition();

			void resetSticksColor();
			void resetSearchStick();
			void resetVariables();

			void processSearchThreadState();
			void joinThreads();
			void initializeSticksArray();
			void processLinearSearch();
			float calculateStickHeight(int array_pos);

			void destroy();
		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void update();
			void render();

			void reset();
			void searchElement(SearchType search_type);

			SearchType getSearchType();

			int getNumberOfSticks();
			int getNumberOfComparisons();
			int getNumberOfArrayAccess();
			int getDelayMilliseconds();

			sf::String getTimeComplexity();
		};
	}
}