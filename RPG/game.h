#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "player.h"
#include "Map.h"

using namespace std;
using namespace sf;

enum class GameState { MENU, MENU2, MENU2_a, MENU2_b, MENU2_c, GAME, GAME_OVER, END, UNKNOWN };
enum class NPC_Type {fighter, archer};

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
	void addNPC(vector<NPC*>& GamePlayers, pair<int, int> location, bool archer);
	String atack(Player* player, vector<NPC*>& list, int number, RenderWindow& okno);
	bool isEnemy(pair<int, int> kordy);
	int whoIs(pair<int, int> kordy);
	String NPCturn(Player* player, NPC* wrog, RenderWindow& okno);
	pair<int, int> wayToPlayer(Player* player, NPC* wrog);
	//dodaæ wyj¹tki

protected:
	GameState state;
	Texture background, background2, background3, background4;
	Sprite bg;
	Font font;
	RenderWindow window;
	Player* Gracz;
	vector<NPC*> NPCPlayers;
	vector<pair<int, int>>* NPCposition;
	Map mapa;

};


