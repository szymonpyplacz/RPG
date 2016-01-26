#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "game.h"
#include "Dice.h"

using namespace std;
using namespace sf;

int main(){
	FreeConsole();
	{	Game game;
	game.runGame();
	}
	_CrtDumpMemoryLeaks();
}
