#pragma once
#include"UI/UIElement/RectangleShapeView.h"

namespace Gameplay
{
	namespace Collection
	{
		struct Stick
		{
		private:
			int data;
			UI::UIElement::RectangleShapeView* stick_view;

		public:
			Stick(int data)
			{
				this->data = data;
				stick_view = new UI::UIElement::RectangleShapeView();
			}

			~Stick()
			{
				delete(stick_view);
			}
		};
	}
}