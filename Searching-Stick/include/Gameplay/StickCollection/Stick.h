#pragma once
#include<SFML/Graphics.hpp>
#include"UI/UIElement/RectangleShapeView.h"

namespace Gameplay
{
	namespace Collection
	{
		struct Stick
		{
		
			int data;
			UI::UIElement::RectangleShapeView* stick_view;

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