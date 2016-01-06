#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "player.h"

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
	void khelgar(Player* Gracz);
	void tharwen(Player* Gracz);
	void rodger(Player* Gracz);
	void gamePlay(Player* Gracz);
	void printPlayer(Player* Gracz);
	void nextTurn();
	//dodaæ wyj¹tki

protected:
	GameState state;
	Texture background, background2, background3, background4;
	Sprite bg;
	Font font;
	RenderWindow window;
	Player* Gracz;

};


