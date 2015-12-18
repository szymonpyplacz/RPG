#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

class printText
{
public:
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<float, float> kordy);
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<float, float> kordy, GameState state);
	Text& GetText();
	GameState GetState() const;
	Color& setColor();

private:
	sf::Text printedText;
	sf::Color fontColor;
	GameState goTo;
	bool visible;
};