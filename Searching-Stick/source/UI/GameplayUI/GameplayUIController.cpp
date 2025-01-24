#include"UI/GameplayUI/GameplayUIController.h"
#include"Global/Config.h"
#include"Global/ServiceLocator.h"
#include"Gameplay/GameplayService.h"
#include"Sound/SoundService.h"
#include"Main/GameService.h"
#include"Gameplay/StickCollection/StickCollectionModel.h"

namespace UI
{
	namespace GameplayUI
	{
		using namespace Global;
		using namespace UIElement;
		using namespace Gameplay;
		using namespace Sound;
		using namespace Main;
		using namespace Collection;

		GameplayUIController::GameplayUIController()
		{
			createButton();
			createTexts();
		}

		GameplayUIController::~GameplayUIController()
		{
			destroy();
		}

		void GameplayUIController::initialize()
		{
			initializeButtons();
			initializeText();
			updateSearchTypeText();
		}

		void GameplayUIController::update()
		{
			menu_button->update();

			updateSearchTypeText();
			updateComparisonText();
			updateArrayAccessText();
			updateNumberOfSticksText();
			updateDelayText();
			updateTimeComplexityText();
		}
		
		void GameplayUIController::render()
		{
			menu_button->render();
			search_type->render();
			number_of_comparisons->render();
			number_of_array_access->render();
			number_of_sticks->render();
			delay_text->render();
			time_complexity_text->render();
		}

		void GameplayUIController::show()
		{
			menu_button->show();
			search_type->show();
			number_of_comparisons->show();
			number_of_array_access->show();
			number_of_sticks->show();
			delay_text->show();
			time_complexity_text->show();
		}

		void GameplayUIController::createButton()
		{
			menu_button = new ButtonView();
		}

		void GameplayUIController::createTexts()
		{
			search_type = new TextView();
			number_of_comparisons = new TextView();
			number_of_array_access = new TextView();
			number_of_sticks = new TextView();
			delay_text = new TextView();
			time_complexity_text = new TextView();
		}

		void GameplayUIController::initializeButtons()
		{
			menu_button->initialize("Menu Button", Config::menu_button_texture_path, button_width, button_height, sf::Vector2f(menu_button_x_position, menu_button_y_position));
			registerButtonCallback();
		}

		void GameplayUIController::initializeText()
		{
			search_type->initialize("Search Type  :  Linear Search", sf::Vector2f(search_type_text_x_position, text_y_position_1), FontType::BUBBLE_BOBBLE, font_size);
			number_of_comparisons->initialize("Comparisons  :  0", sf::Vector2f(comparison_text_x_position, text_y_position_1), FontType::BUBBLE_BOBBLE, font_size);
			number_of_array_access->initialize("Array Access  :  0", sf::Vector2f(array_access_text_x_position, text_y_position_1), FontType::BUBBLE_BOBBLE, font_size);
			number_of_sticks->initialize("Number of Sticks  :  0", sf::Vector2f(num_sticks_text_x_position, text_y_position_2), FontType::BUBBLE_BOBBLE, font_size);
			delay_text->initialize("Delay  :  0 ms", sf::Vector2f(delay_text_x_position, text_y_position_2), FontType::BUBBLE_BOBBLE, font_size);
			time_complexity_text->initialize("Time Complexity  :  O(n)", sf::Vector2f(time_complexity_text_x_position, text_y_position_2), FontType::BUBBLE_BOBBLE, font_size);
		}

		void GameplayUIController::updateSearchTypeText()
		{
			Collection::SearchType new_search_type = ServiceLocator::getInstance()->getGameplayService()->getCurrentSearchType();
			switch (new_search_type)
			{
			case Collection::SearchType::LINEAR_SEARCH:
				search_type->setText("Linear Search");
				break;
			}
			search_type->update();
		}

		void GameplayUIController::updateComparisonText()
		{
			int num_of_comparisons = ServiceLocator::getInstance()->getGameplayService()->getNumberOfComparisons();;
			sf::String comparisons_string = "Comparisons  :  " + std::to_string(num_of_comparisons);
			number_of_comparisons->setText(comparisons_string);
			number_of_comparisons->update();
		}

		void GameplayUIController::updateArrayAccessText()
		{
			int num_of_array_access = ServiceLocator::getInstance()->getGameplayService()->getNumberOfArrayAccess();;
			sf::String array_access_string = "Array Access  :  " + std::to_string(num_of_array_access);
			number_of_array_access->setText(array_access_string);
			number_of_array_access->update();
		}

		void GameplayUIController::updateNumberOfSticksText()
		{
			int num_sticks = ServiceLocator::getInstance()->getGameplayService()->getNumberOfSticks();
			sf::String sticks_string = "Number of Sticks  :  " + std::to_string(num_sticks);
			number_of_sticks->setText(sticks_string);
			number_of_sticks->update();
		}

		void GameplayUIController::updateDelayText()
		{
			int delay_in_milliseconds = ServiceLocator::getInstance()->getGameplayService()->getDelayMilliseconds();
			sf::String delay_string = "Delay (ms)  :  " + std::to_string(delay_in_milliseconds);
			delay_text->setText(delay_string);
			delay_text->update();
		}

		void GameplayUIController::updateTimeComplexityText()
		{
			sf::String time_complexity = ServiceLocator::getInstance()->getGameplayService()->getTimeComplexity();
			sf::String time_complexity_string = "Time Complexity  :  " + time_complexity;
			time_complexity_text->setText(time_complexity_string);
			time_complexity_text->update();
		}

		void GameplayUIController::menuButtonCallback()
		{
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
			ServiceLocator::getInstance()->getGameplayService()->reset();
			GameService::setGameState(GameState::MAIN_MENU);
		}

		void GameplayUIController::registerButtonCallback()
		{
			menu_button->registerCallbackFuntion(std::bind(&GameplayUIController::menuButtonCallback, this));
		}

		void GameplayUIController::destroy()
		{
			delete(menu_button);
			delete(search_type);
			delete(number_of_comparisons);
			delete(number_of_array_access);
			delete(time_complexity_text); 
			delete(number_of_sticks);
			delete(delay_text);
		}
	}
}