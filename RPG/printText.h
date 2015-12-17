#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

class printText
{
	sf::Text printedText;
	sf::Color fontColor;
	GameState goTo;
	bool visible;
	

public:
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, float x, float y, bool visibility = true) :printedText(text, font, characterSize), visible(visibility), fontColor(textColor)
	{
		printedText.setPosition(x, y);
		printedText.setColor(textColor);
		goTo = GameState::UNKNOWN;
	}

	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, float x, float y, GameState state, bool visibility = true) :printedText(text, font, characterSize), visible(visibility), goTo(state), fontColor(textColor)
	{
		printedText.setPosition(x, y);
		printedText.setColor(textColor);
	}
	sf::Text& GetText()	{	
		return printedText;
	}
	GameState GetState() const	{
		return goTo;
	}
	bool IsVisible() const{
		return visible;
	}
	sf::Color& setColor(){
		return fontColor;
	}
};