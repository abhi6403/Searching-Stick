#pragma once
#include"UI/Interface/IUIController.h"
#include"UI/UIElement/ButtonView.h"
#include"UI/UIElement/TextView.h"
#include"Gameplay/GameplayService.h"

namespace UI
{
	namespace GameplayUI
	{
		class GameplayUIController : public Interface::IUIController
		{
		private:
			const float button_width = 100.f;
			const float button_height = 50.f;

			const float font_size = 40.f;

			const float text_y_position_1 = 36.f;
			const float text_y_position_2 = 76.f;

			const float search_type_text_x_position = 480.f;
			const float comparison_text_x_position = 960.f;
			const float array_access_text_x_position = 1440.f;
			const float num_sticks_text_x_position = 480.f;
			const float delay_text_x_position = 960.f;
			const float time_complexity_text_x_position = 1440.f;

			const float menu_button_x_position = 80.f;
			const float menu_button_y_position = 30.f;

			UIElement::ButtonView* menu_button;

			UIElement::TextView* search_type;
			UIElement::TextView* number_of_comparisons;
			UIElement::TextView* number_of_array_access;
			UIElement::TextView* number_of_sticks;
			UIElement::TextView* delay_text;
			UIElement::TextView* time_complexity_text;

			void createButton();
			void createTexts();

			void initializeButtons();
			void initializeText();

			void updateSearchTypeText();
			void updateComparisonText();
			void updateArrayAccessText();
			void updateNumberOfSticksText();
			void updateDelayText();
			void updateTimeComplexityText();

			void registerButtonCallback();
			void menuButtonCallback();

			void destroy();
		public:
			GameplayUIController();
			~GameplayUIController();

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
		};
	}
}