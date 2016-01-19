#pragma once
#include "DetectMemoryLeaks.h"
#include "DetectMemoryLeaks.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Windows.h>
#include <string>
#include "player.h"
#include "Map.h"
#include <vector>
#include "printSprite.h"
#include "Terrain.h"
#include <fstream>
#include <sstream>




using namespace std;
using namespace sf;

enum class GameState { MENU, MENU2, MENU2_a, MENU2_b, MENU2_c, GAME, GAME_OVER, END, WIN, LOSE, UNKNOWN };
enum class NPC_Type {fighter, archer};

class Game
{
public:
	Game(void);
	void runGame();
	void menu();
	void newPlayer();
	void winGame();
	void loseGame();
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
	Sprite& addPhoto(Sprite& sprite, Texture& texture, string filename);
	void attackLeft(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch);
	void attackLeftTop(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch);
	void attackLeftDown(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch);
	void attackRight(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch);
	void attackRightTop(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch);
	void attackRightDown(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch);
	void attackTop(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch);
	void attackDown(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch);
	void setMap(Player* gracz, RenderWindow& okno, Map& mapa, bool created, int left, int right, int top, int down, vector<printSprite>& obrazy);
	void setMapFormFile(Player* gracz, RenderWindow& okno, Map& mapa, bool created, vector<printSprite>& obrazy, string filename);
	void addNPCsFromFile(vector<NPC*>& GamePlayers, string filename);
	void endPlayerTurn(RenderWindow& window, Player* gracz, vector<NPC*>& list, bool endTurn, vector<printSprite>& obrazy, Text& ruch, Sprite& hpBar, string& hp, Text& printHpLine);
	

protected:
	Grass trawa;
	Hill gory;
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
