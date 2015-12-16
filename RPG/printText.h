#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

class printText
{
	sf::Text printedText;
	GameState goTo;
	bool visible;
public:
	printText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float x, float y, GameState state, bool visibility = true) :printedText(text, font, characterSize), goTo(state), visible(visibility)
	{
		printedText.setPosition(x, y);
	}
	sf::Text& GetText()
	{	
		this->printedText.setColor(Color::Black);
		return printedText;
	}
	GameState GetState() const
	{
		return goTo;
	}
	bool IsVisible() const
	{
		return visible;
	}
};