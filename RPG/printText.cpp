#include "printText.h"
#include "game.h"
#include <SFML\Graphics.hpp>
#pragma once

printText::printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<int, int> kordy) :printedText(text, font, characterSize), fontColor(textColor)
	{
		printedText.setPosition(kordy.first, kordy.second);
		printedText.setColor(textColor);
		goTo = GameState::UNKNOWN;
	}

printText::printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<int, int> kordy, GameState state) :printedText(text, font, characterSize), goTo(state), fontColor(textColor)
	{
		printedText.setPosition(kordy.first, kordy.second);
		printedText.setColor(textColor);
	}

printText::printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<int, int> kordy, Player* gracz, Orders metoda) :printedText(text, font, characterSize), method(metoda), fontColor(textColor)
{
	goTo = GameState::UNKNOWN;
	printedText.setPosition(kordy.first, kordy.second);
	printedText.setColor(textColor);
}

Orders printText::getOrder(){
	return method;
}

Text& printText::GetText()	{
		return printedText;
	}

GameState printText::GetState() const	{
		return goTo;
	}

Color& printText::setColor(){
		return fontColor;
	}
