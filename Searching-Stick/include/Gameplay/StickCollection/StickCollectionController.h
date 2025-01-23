#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

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
			StickCollectionView* collection_view;
			StickCollectionModel* collection_model;

			std::vector<Stick*>sticks;

			Collection::SearchType search_type;

			void initializeSticks();
			float calculateStickWidth();

			void updateSticksPosition();

			void resetSticksColor();

			void initializeSticksArray();
			float CalculateStickHeight(int array_pos);

			void destroy();
		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void update();
			void render();

			void reset();

			SearchType getSearchType();

			int getNumberOfSticks();
		};
	}
}