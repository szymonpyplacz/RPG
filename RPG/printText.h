#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "player.h"

enum class Orders { ChangeWeapon };

class printText
{
public:
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<int, int> kordy);
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<int, int> kordy, GameState state);
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<int, int> kordy, Player* gracz, Orders metoda);
	Text& GetText();
	GameState GetState() const;
	Color& setColor();
	Orders getOrder();

private:
	sf::Text printedText;
	sf::Color fontColor;
	GameState goTo;
	Orders method;
};