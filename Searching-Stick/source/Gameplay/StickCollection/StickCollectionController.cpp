#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include "Gameplay/StickCollection/Stick.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"
#include <iostream>
#include<random>
#include<thread>

namespace Gameplay 
{
	namespace Collection 
	{

		using namespace UI::UIElement;
		using namespace Global;
		using namespace Graphics;
		using namespace Sound;

		StickCollectionController::StickCollectionController()
		{
			collection_view = new StickCollectionView();
			collection_model = new StickCollectionModel();
			initializeSticksArray();
		}

		StickCollectionController::~StickCollectionController()
		{
			destroy();
		}

		void StickCollectionController::initialize()
		{

			initializeSticks();
			reset();
		}

		void StickCollectionController::update()
		{
			processSearchThreadState();

			collection_view->update();

			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->update();
		}

		void StickCollectionController::render()
		{
			collection_view->render();

			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->render();
		}

		void StickCollectionController::reset()
		{
			current_operation_delay = 0;

			if (search_thread.joinable())
			{
				search_thread.join();
			}

			shuffleSticks();
			updateSticksPosition();
			resetSticksColor();
			resetSearchStick();
			resetVariables();
		}
		void StickCollectionController::initializeSticks()
		{
			float rectangle_width = calculateStickWidth();


			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				float rectangle_height = calculateStickHeight(i); //calc height

				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);

				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, collection_model->element_color);
			}
		}

		float StickCollectionController::calculateStickWidth()
		{
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);

			// Calculate total spacing as 10% of the total space
			float total_spacing = collection_model->space_percentage * total_space;

			// Calculate the space between each stick
			float space_between = total_spacing / (collection_model->number_of_elements - 1);
			collection_model->setElementSpacing(space_between);

			// Calculate the remaining space for the rectangles
			float remaining_space = total_space - total_spacing;

			// Calculate the width of each rectangle
			float rectangle_width = remaining_space / collection_model->number_of_elements;

			return rectangle_width;
		}

		void StickCollectionController::updateSticksPosition()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				float x_position = (i * sticks[i]->stick_view->getSize().x) + ((i + 1) * collection_model->elements_spacing);
				float y_position = collection_model->element_y_position - sticks[i]->stick_view->getSize().y;

				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}

		void StickCollectionController::shuffleSticks()
		{
			std::random_device device;
			std::mt19937 random_engine(device());

			std::shuffle(sticks.begin(), sticks.end(), random_engine);
		}


		void StickCollectionController::processLinearSearch()
		{
			SoundService* sound_service = ServiceLocator::getInstance()->getSoundService();
			for (int i = 0; i < sticks.size(); i++)
			{
				sound_service->playSound(SoundType::COMPARE_SFX);
				number_of_array_access += 1;
				number_of_comparisons++;

				if (sticks[i] == stick_to_search)
				{
					stick_to_search->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;
					return;
				}
				else
				{
					sticks[i]->stick_view->setFillColor(collection_model->processing_element_color);
					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));
					sticks[i]->stick_view->setFillColor(collection_model->element_color);
				}

			}
		}

		void StickCollectionController::sortElements()
		{
			std::sort(sticks.begin(), sticks.end(), [this](const Stick* a, const Stick* b) { return compareElementsByData(a, b); });

			updateSticksPosition();
		}

		bool StickCollectionController::compareElementsByData(const Stick* a, const Stick* b) const
		{

			// if 'a->data' is less than 'b->data', the expression evaluates to true which indicates that 'a' should precede 'b' in the sorted order.
			return a->data < b->data;
		}

		void StickCollectionController::processBinarySearch()
		{
			// initialize left index to the start of the collection
			int left = 0;

			// initialize right index to the size of the collection which is the end
			int right = sticks.size();

			Sound::SoundService* sound_service = Global::ServiceLocator::getInstance()->getSoundService();

			// loop for binary search
			while (left < right)
			{

				// calculate the middle index
				int mid = left + (right - left) / 2;
				number_of_array_access += 2;				//keeps track of the number of sticks array is accessed
				number_of_comparisons++;					// keeps track of the number of comparisons made between target stick and another stick

				sound_service->playSound(Sound::SoundType::COMPARE_SFX);			// play comparison sound effect

				// check if target element is found at the middle index
				if (sticks[mid] == stick_to_search)
				{
					// if the target element is found, set color for found element
					sticks[mid]->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;			//ets the pointer to null; meaning the search is completed
					return;
				}

				sticks[mid]->stick_view->setFillColor(collection_model->processing_element_color);			// if mid is not the target element, set the stick color to processing element color
				std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));			// //pauses the thread for a small duration to show the searching operation
				sticks[mid]->stick_view->setFillColor(collection_model->element_color);			// sets the fill color of the mid stick's view back to the default element_color after the pause.


				number_of_array_access++;			// increment counter for array access for mid element access

				// target can be in the right half or middle element itself
				if (sticks[mid]->data <= stick_to_search->data) left = mid;				// target must be in the right half, mid element included beacuse '<='
				else right = mid;				// target must be in the left half
			}
		}

		void StickCollectionController::processSearchThreadState()
		{
			if (search_thread.joinable() && stick_to_search == nullptr)
			{
				joinThreads();
			}
		}

		void StickCollectionController::joinThreads()
		{
			search_thread.join();
		}

		void StickCollectionController::resetSticksColor()
		{
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->setFillColor(collection_model->element_color);
		}

		void StickCollectionController::resetSearchStick()
		{
			stick_to_search = sticks[std::rand() % sticks.size()];
			stick_to_search->stick_view->setFillColor(collection_model->search_element_color);
		}

		void StickCollectionController::resetVariables()
		{
			number_of_comparisons = 0;
			number_of_array_access = 0;
		}

		void StickCollectionController::initializeSticksArray()
		{
			for (int i = 0; i < collection_model->number_of_elements; i++)
				sticks.push_back(new Stick(i));
		}

		float StickCollectionController::calculateStickHeight(int array_pos)
		{
			return (static_cast<float>(array_pos + 1) / collection_model->number_of_elements) * collection_model->max_element_height;
		}

		void StickCollectionController::destroy()
		{
			if (search_thread.joinable())
			{
				search_thread.join();
			}

			for (int i = 0; i < sticks.size(); i++) delete(sticks[i]);
			sticks.clear();

			delete (collection_view);
			delete (collection_model);
		}

		void StickCollectionController::searchElement(SearchType search_type)
		{
			this->search_type = search_type;

			switch (search_type)
			{
			case Gameplay::Collection::SearchType::LINEAR_SEARCH:
				time_complexity = "O(n)";
				current_operation_delay = collection_model->linear_search_delay;
				search_thread = std::thread(&StickCollectionController::processLinearSearch, this);
				break;
			case Gameplay::Collection::SearchType::BINARY_SEARCH:
				sortElements();
				time_complexity = "O(log n)";
				current_operation_delay = collection_model->binary_search_delay;
				search_thread = std::thread(&StickCollectionController::processBinarySearch, this);
				break;
			default:
				break;
			}
		}

		SearchType StickCollectionController::getSearchType()
		{
			return search_type;
		}

		int StickCollectionController::getNumberOfSticks()
		{
			return collection_model->number_of_elements;
		}

		int StickCollectionController::getNumberOfComparisons()
		{
			return number_of_comparisons;
		}

		int StickCollectionController::getNumberOfArrayAccess()
		{
			return number_of_array_access;
		}

		int StickCollectionController::getDelayMilliseconds()
		{
			return current_operation_delay;
		}

		sf::String StickCollectionController::getTimeComplexity()
		{
			return time_complexity;
		}
	}
}