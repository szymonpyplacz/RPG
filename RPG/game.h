#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>

using namespace std;
using namespace sf;

enum class GameState { MENU, MENU2, MENU2_a, MENU2_b, MENU2_c, GAME, GAME_OVER, END, UNKNOWN };

class Game
{
public:
	Game(void);
	void runGame();
	void menu();
	void newPlayer();
	void khelgar();
	void tharwen();
	void rodger();

protected:

	GameState state;
	Texture background, background2, background3;
	Sprite bg;
	Font font;
	sf::RenderWindow window;

private: 
};


