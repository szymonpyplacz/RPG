#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "player.h"

enum class Orders { ChangeWeapon };

class printText
{
public:
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<float, float> kordy);
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<float, float> kordy, GameState state);
	printText(const sf::String& text, const sf::Font& font, Color textColor, unsigned int characterSize, pair<float, float> kordy, Player* gracz, Orders metoda);
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