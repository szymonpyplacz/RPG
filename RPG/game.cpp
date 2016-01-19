#pragma once
#include "game.h"
#include <Windows.h>
#include "printText.h"

//24 punkty do budowy postaci

Game::Game(void) : window(VideoMode(1280, 720, 32), "", Style::None)
{
	window.setPosition(Vector2i(300, 100));
	window.setKeyRepeatEnabled(true);
	state = GameState::END;


	if ((!background.loadFromFile("bg3.jpg")) || (!background2.loadFromFile("bg2.jpg")) || (!background3.loadFromFile("bg.gif")) || (!background4.loadFromFile("bg4.png")))
		return;

	state = GameState::MENU;

	if (!font.loadFromFile("font_one.ttf"))	{
		MessageBox(NULL, "Font not found", "ERROR", NULL);
		return;
	}
	state = GameState::MENU;
};


void Game::runGame()
{
	while (state != GameState::END)
	{
		Music muzyka;
		muzyka.openFromFile("arise.ogg");
		//muzyka.play();
		//muzyka.setVolume(30);

		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::MENU2:{
			newPlayer();
			break;
		}
		case GameState::MENU2_a:{
									Player* Gracz = new Player(playerClass::fighter, rase::dwarf, Ability(15), Ability(12), Ability(14), Ability(10), Ability(10), Ability(10), Level(0), Armor(), true, "Khelgar");
									Gracz->setMainWeapon(WeaponCollection::SmallAxe);
									Gracz->setDistanceWeapon(WeaponCollection::Crossbow);
									Gracz->setShield(WeaponCollection::LightShield); //logicial error, TH weapon with shield is impossible
									Gracz->setArmour(WeaponCollection::MailShirt);
									printPlayer(Gracz);
									if (state == GameState::GAME)
									gamePlay(Gracz);
									break; }
		case GameState::MENU2_b:{
									Player* Gracz = new Player(playerClass::wizard, rase::human, Ability(8), Ability(12), Ability(10), Ability(16), Ability(14), Ability(10), Level(0), Armor(), true, "Rodger");
									Gracz->setMainWeapon(WeaponCollection::Fist); //trolololo i tak nie mo¿e
									Gracz->setDistanceWeapon(WeaponCollection::Slingshot);
									Gracz->setArmour(WeaponCollection::LeatherArmor);//trololo i tak nie mo¿e
									Gracz->setShield(WeaponCollection::LightShield);
									printPlayer(Gracz);
									if (state == GameState::GAME)
									gamePlay(Gracz);
									break;}
		case GameState::MENU2_c:{
									Player* Gracz = new Player(playerClass::hunter, rase::elf, Ability(15), Ability(14), Ability(12), Ability(10), Ability(10), Ability(10), Level(0), Armor(), false, "Tharwen");
									Gracz->setMainWeapon(WeaponCollection::Longsword);
									Gracz->setDistanceWeapon(WeaponCollection::Longbow);
									Gracz->setArmour(WeaponCollection::LeatherArmor);
									printPlayer(Gracz);
									if (state == GameState::GAME)
									gamePlay(Gracz);
									break; }
		case GameState::WIN:{
			winGame();
			break;
		}
		case GameState::LOSE:{
			loseGame();
			break; }
		}
	}
}


void Game::menu()
{
	bg.setTexture(background2);
	vector<printText> button;
	button.emplace_back(L"Witaj dzielny œmia³ku, \nOd Twojego zadania\n  Zale¿¹ losy\n  nas wszystkich", font, Color::Black, 48, pair<int, int>(300, 20));
	button.emplace_back(L"Nowa Gra", font, Color::Black, 36, pair<int, int>(650, 300), GameState::MENU2);
	button.emplace_back(L"Graj dalej", font, Color::Black, 36, pair<int, int>(650, 350));
	button.emplace_back(L"WyjdŸ z gry", font, Color::Black, 36, pair<int, int>(700, 500), GameState::END);

	printText* hoverPrintText = nullptr;
	while (state == GameState::MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		hoverPrintText = nullptr;

		for (auto& button : button)
		if ((button.GetText().getGlobalBounds().contains(mouse)) && (button.GetState() != GameState::UNKNOWN))
		{
			button.GetText().setStyle(Text::Underlined);
			hoverPrintText = &button;
		}
		else
		{
			button.GetText().setStyle(Text::Regular);
		}
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverPrintText)
			{
				if (hoverPrintText->GetState() != GameState::UNKNOWN )
				state = hoverPrintText->GetState();
				break;
			}
		}
		window.clear();
		window.draw(bg);
		for (auto &button : button)
		{
				button.GetText().setColor(button.setColor());
				window.draw(button.GetText());
		}
		window.display();
	}
}

void Game::newPlayer(){
	bg.setTexture(background);
	vector<printText> button;
	button.emplace_back(L"Wybierz któregoœ z bohaterów", font, Color::Black, 48, pair<int, int>(120, 20));
	button.emplace_back(L"Khelgar, krasnolud wojownik", font, Color::Black, 32, pair<int, int>(120, 200), GameState::MENU2_a);
	button.emplace_back(L"Rodger, mag cz³owiek", font, Color::Black, 32, pair<int, int>(120, 260), GameState::MENU2_b);
	button.emplace_back(L"Thárwen, elfka tropiciel", font, Color::Black, 32, pair<int, int>(120, 320), GameState::MENU2_c);
	button.emplace_back(L"Powrót", font, Color::Black, 32, pair<int, int>(120, 600), GameState::MENU);

	printText* hoverPrintText = nullptr;
	while (state == GameState::MENU2)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		hoverPrintText = nullptr;

		for (auto& button : button){
		if ((button.GetText().getGlobalBounds().contains(mouse)) && (button.GetState() != GameState::UNKNOWN))
		{

			button.GetText().setStyle(Text::Underlined);
			hoverPrintText = &button;
		}

		else
		{
			button.GetText().setStyle(Text::Regular);
		}
		}
		while (window.pollEvent(event))
		{
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverPrintText)
			{
				if (hoverPrintText->GetState() != GameState::UNKNOWN)
					state = hoverPrintText->GetState();
				break;
			}
		}
		window.clear();
		window.draw(bg);
		for (auto &button : button)
		{
				button.GetText().setColor(button.setColor());
				window.draw(button.GetText());

		}
		window.display();
	}
}


void::Game::printPlayer(Player* Gracz) {
	bg.setTexture(background3);
//	GamePlayers.emplace_back(Gracz);
	Texture wood;
	wood.loadFromFile("belka.gif");
	Sprite woodSprite;
	woodSprite.setTexture(wood);
	vector<printSprite> buttonImg;
	buttonImg.emplace_back(woodSprite, pair<int, int>(430, 35));
	buttonImg.emplace_back(woodSprite, pair<int, int>(820, 35));
	buttonImg.emplace_back(Gracz->printAvatar(), pair<int, int>(45, 40));
	buttonImg.emplace_back(Gracz->getMainWeapon().printSprite(), pair<int, int>(50, 360));
	buttonImg.emplace_back(Gracz->getSecondWeapon().printSprite(), pair<int, int>(50, 460));
	buttonImg.emplace_back(Gracz->getShield().printSprite(), pair<int, int>(470, 360));
	buttonImg.emplace_back(Gracz->getArmour().printSprite(), pair<int, int>(470, 460));
	Color gold(252, 255, 166);

	string s = Gracz->printStr();
	string d = Gracz->printDex();
	string c = Gracz->printCon();
	string i = Gracz->printInt();
	string w = Gracz->printWis();
	string ch = Gracz->printCha();
	string className = Gracz->printClassName();
	string raseName = Gracz->printRaseName();
	string name = Gracz->printName();
	string hp = ("PW: " + to_string(Gracz->getHp().printHP()) + "/" + to_string(Gracz->getHp().printMaxHP()));
	string ac = ("KP: " + to_string(Gracz->printAC()));
	sf::String distance = Gracz->getSecondWeapon().printName() + " poc. " + to_string(Gracz->getSecondWeapon().printMissles()) + L" zasiêg " + to_string(Gracz->getSecondWeapon().printRange()) + "\n1k" + to_string(Gracz->getSecondWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getSecondWeapon().printCr()) + "/" + Gracz->getSecondWeapon().printCrRg();
	if (Gracz->getSecondWeapon().printName() == "Brak broni dystansowej")
		distance = Gracz->getSecondWeapon().printName();
	sf::String shield = "+" + to_string(Gracz->getShield().getAC()) + " KP";
	if (Gracz->getShield().getAC() == 0)
		shield = "";
	sf::String armour = "+" + to_string(Gracz->getArmour().getAC()) + " KP";
	if (Gracz->getArmour().getAC() == 0)
		armour = "";

	vector<printText> button;
	button.emplace_back(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Gracz->printLvl()) + "\n\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()), font, gold, 28, pair<int, int>(260, 50));
	button.emplace_back(hp + "\n\n" + L"Premia do ataku: \n\nPrêdkoœæ \n\nWytrwa³oœæ: \n\nRefleks: \n\nWola: ", font, gold, 22, pair<int, int>(490, 50));
	button.emplace_back(ac + "\n\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n\n" + to_string(Gracz->printSpeed()) + "\n\n" + to_string(Gracz->printSTFor()) + "\n\n" + to_string(Gracz->printSTRef()) + "\n\n" + to_string(Gracz->printSTWl()), font, gold, 22, pair<int, int>(720, 50));
	button.emplace_back(L"Si³a: \n\nZrêcznoœæ: \n\nWytrzyma³oœæ: \n\nIntelekt: \n\nRozs¹dek: \n\nCharyzma: ", font, gold, 22, pair<int, int>(900, 50));
	button.emplace_back(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, gold, 22, pair<int, int>(1130, 50));
	button.emplace_back(Gracz->getMainWeapon().printName() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, gold, 24, pair<int, int>(125, 370));
	button.emplace_back(distance, font, gold, 24, pair<int, int>(125, 470));
	button.emplace_back(Gracz->getShield().printName() + "\n" + shield, font, gold, 22, pair<int, int>(550, 370));
	button.emplace_back(Gracz->getArmour().printName() + "\n" + armour, font, gold, 22, pair<int, int>(550, 470));
	button.emplace_back(L"Powrót", font, gold, 28, pair<int, int>(200, 600), GameState::MENU2);
	button.emplace_back(L"Dalej", font, gold, 28, pair<int, int>(800, 600), GameState::GAME);

	printText* hoverPrintText = nullptr;
	while (state == GameState::MENU2_a || state == GameState::MENU2_c || state == GameState::MENU2_b )
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		hoverPrintText = nullptr;

		for (auto& button : button){
			if ((button.GetText().getGlobalBounds().contains(mouse)) && (button.GetState() != GameState::UNKNOWN))
			{
				button.GetText().setStyle(Text::Underlined);
				hoverPrintText = &button;
			}
			else
			{
				button.GetText().setStyle(Text::Regular);
				button.GetText().setColor(Color::Black);
			}
		}
		while (window.pollEvent(event))
		{
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverPrintText)
			{
				if (hoverPrintText->GetState() != GameState::UNKNOWN)
					state = hoverPrintText->GetState();
				break;
			}
		}
		window.clear();
		window.draw(bg);
		for (auto &button : button)
		{
			button.GetText().setColor(button.setColor());
			window.draw(button.GetText());
		}
		for (auto& button : buttonImg){
			window.draw(button.GetSprite());
		}
		window.display();
	}
}

void::Game::addNPC(vector<NPC*>& listaGraczy, pair<int, int> location, bool isArcher){
	if (isArcher){
		NPC* enemy = new NPC(true, Ability(10), Ability(12), Ability(10), Ability(10), Ability(10), Ability(10), Level(0), Armor());
		enemy->setMainWeapon(WeaponCollection::Dagger);
		enemy->setDistanceWeapon(WeaponCollection::Bow);
		enemy->setArmour(WeaponCollection::LeatherArmor);
		enemy->setPosition(location.first, location.second, mapa);
		listaGraczy.emplace_back(enemy);
	}
	else{
		NPC* enemy = new NPC(false, Ability(12), Ability(10), Ability(10), Ability(10), Ability(10), Ability(10), Level(0), Armor());
		enemy->setMainWeapon(WeaponCollection::Dagger);
		enemy->setArmour(WeaponCollection::Gambeson);
		enemy->setPosition(location.first, location.second, mapa);
		listaGraczy.emplace_back(enemy);
	}
}

String Game::atack(Player* player, vector<NPC*>& enemy, int number, RenderWindow& okno){
	Dice k20(20);
	Color green(103, 190, 75);
	int damage = 0;
	int roll = k20.rollDice();
	string killThemAll = "";
	if (roll + (player->printBasicAttack()) >= enemy[number]->printAC()){
		damage = player->getMainWeapon().returnDice().rollDice();
		if (roll >= player->getMainWeapon().printCrRange())
			damage = damage*player->getMainWeapon().printCr();
		enemy[number]->getHp().getDmg(damage);
			if (enemy[number]->getHp().printHP() == 0){
			mapa.freePosition(make_pair(enemy[number]->getPosition().first, enemy[number]->getPosition().second));
			player->getLevel().addExp(enemy[number]->returnExpValue());
			delete *(enemy.begin() + number);
			enemy.erase(enemy.begin() + number);
			killThemAll = "\nZabito wroga!";
			}
	player->endTurn();
	if (roll >= player->getMainWeapon().printCrRange())
	return(L"Wyrzucono: " + to_string(roll) + " + " + to_string(player->printBasicAttack()) + L"\nTrafienie krytyczne!\n\nZadano " + to_string(damage) + L" obra¿eñ" + killThemAll);
	
	else
		return(L"Wyrzucono: " + to_string(roll) + " + " + to_string(player->printBasicAttack()) + L"\nTrafienie!\n\nZadano " + to_string(damage) + L" obra¿eñ" + killThemAll);
	}
	player->endTurn();
	return("Wyrzucono: " + to_string(roll) + " + " + to_string(player->printBasicAttack()) + "\nNie trafiono!");
}

bool Game::isEnemy(pair<int, int> pozycja){
	for (auto& players : NPCPlayers){
		if (players->getPosition().first == pozycja.first && players->getPosition().second == pozycja.second)
			return true;
	}
	return false;
}

int Game::whoIs(pair<int, int> pozycja){
	int it = 0;
	for (auto& players : NPCPlayers){
		if (players->getPosition().first == pozycja.first && players->getPosition().second == pozycja.second)
			return it;
		it++;
	}

}

pair<int, int> Game::wayToPlayer(Player* player, NPC* enemy){
	return make_pair(enemy->getPosition().first - player->getPosition().first, enemy->getPosition().second - player->getPosition().second);
}

String Game::NPCturn(Player* player, NPC* enemy, RenderWindow& okno){
	String out;
	int move = 0;
	enemy->setLeftMove();
	enemy->setCrossedMove();
	while (enemy->printLeftMove() > 0){
		if (wayToPlayer(player, enemy).first < -1 || wayToPlayer(player, enemy).first > 1 || wayToPlayer(player, enemy).second < -1 || wayToPlayer(player, enemy).second > 1){
			if ((wayToPlayer(player, enemy).first  < -1 && wayToPlayer(player, enemy).second  > 1) && mapa.isEmpty(make_pair(enemy->getPosition().first + 1, enemy->getPosition().second - 1))){//prawo góra
				mapa.freePosition(enemy->getPosition());
				enemy->isCrossedMove();
				enemy->setPosition(enemy->getPosition().first + 1, enemy->getPosition().second - 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).first > 1 && wayToPlayer(player, enemy).second > 1) && mapa.isEmpty(make_pair(enemy->getPosition().first - 1, enemy->getPosition().second - 1))){ //lewo góra
				mapa.freePosition(enemy->getPosition());
				enemy->isCrossedMove();
				enemy->setPosition(enemy->getPosition().first - 1, enemy->getPosition().second - 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).first < -1 && wayToPlayer(player, enemy).second  < -1) && mapa.isEmpty(make_pair(enemy->getPosition().first + 1, enemy->getPosition().second + 1))){ //prawo dó³
				mapa.freePosition(enemy->getPosition());
				enemy->isCrossedMove();
				enemy->setPosition(enemy->getPosition().first + 1, enemy->getPosition().second + 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).first  > 1 && wayToPlayer(player, enemy).second  < -1) && mapa.isEmpty(make_pair(enemy->getPosition().first + 1, enemy->getPosition().second + 1))){ //lewo góra
				mapa.freePosition(enemy->getPosition());
				enemy->isCrossedMove();
				enemy->setPosition(enemy->getPosition().first - 1, enemy->getPosition().second + 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).first > 1) && mapa.isEmpty(make_pair(enemy->getPosition().first - 1, enemy->getPosition().second))) {//lewo
				mapa.freePosition(enemy->getPosition());
				enemy->setPosition(enemy->getPosition().first - 1, enemy->getPosition().second, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).first < -1) && mapa.isEmpty(make_pair(enemy->getPosition().first + 1, enemy->getPosition().second))) {//prawo
				mapa.freePosition(enemy->getPosition());
				enemy->setPosition(enemy->getPosition().first + 1, enemy->getPosition().second, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).second  > 1) && mapa.isEmpty(make_pair(enemy->getPosition().first, enemy->getPosition().second - 1))) {//góra
				mapa.freePosition(enemy->getPosition());
				enemy->setPosition(enemy->getPosition().first, enemy->getPosition().second - 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).second < -1) && mapa.isEmpty(make_pair(enemy->getPosition().first, enemy->getPosition().second + 1))) {//dó³
				mapa.freePosition(enemy->getPosition());
				enemy->setPosition(enemy->getPosition().first, enemy->getPosition().second + 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else {
				enemy->setPosition(enemy->getPosition().first, enemy->getPosition().second, mapa);
				mapa.freePosition(enemy->getPosition());
			}
			out = (L"Przeciwnik siê ruszy³");
		}
		else {
			Dice k20(20);
			int damage = 0;
			int roll = k20.rollDice();
			string killThemAll = "";
			if (roll + (enemy->printBasicAttack()) >= player->printAC()){
				damage = enemy->getMainWeapon().returnDice().rollDice();
				if (roll >= enemy->getMainWeapon().printCrRange())
					damage = damage*enemy->getMainWeapon().printCr();
				player->getHp().getDmg(damage);
				if (roll >= enemy->getMainWeapon().printCrRange())
				out = (L"Wróg wyrzuci³: " + to_string(roll) + " + " + to_string(enemy->printBasicAttack()) + L"\nTrafienie krytyczne!\n\nZadano " + to_string(damage) + L" obra¿eñ" + killThemAll);
		
				else
				out = (L"Wróg wyrzuci³: " + to_string(roll) + " + " + to_string(enemy->printBasicAttack()) + L"\nTrafienie!\n\nZadano " + to_string(damage) + L" obra¿eñ" + killThemAll);

				player->endTurn();
				}
			else
				out = (L"Wróg wyrzuci³: " + to_string(roll) + " + " + to_string(player->printBasicAttack()) + "\nNie trafiono!");
				enemy->endTurn();
		}
	}
	return out;
}

Sprite& Game::addPhoto(Sprite& sprite, Texture& textura, std::string filename){
	textura.loadFromFile(filename);
	sprite.setTexture(textura);
	return sprite;
}

void Game::attackLeft(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch){
	info.setString(atack(gracz, list, whoIs(make_pair(gracz->getPosition().first - 1, gracz->getPosition().second)), window));
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	level.setString("Poziom: " + to_string(gracz->printLvl()) + "\nPD: " + to_string(gracz->printExp()) + "/" + to_string(gracz->printExpToLv()));
}

void Game::attackLeftTop(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch){
	info.setString(atack(gracz, NPCPlayers, whoIs(make_pair(gracz->getPosition().first - 1, gracz->getPosition().second - 1)), window));
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	level.setString("Poziom: " + to_string(gracz->printLvl()) + "\nPD: " + to_string(gracz->printExp()) + "/" + to_string(gracz->printExpToLv()));
}
void Game::attackLeftDown(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch){
	info.setString(atack(gracz, NPCPlayers, whoIs(make_pair(gracz->getPosition().first - 1, gracz->getPosition().second + 1)), window));
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	level.setString("Poziom: " + to_string(gracz->printLvl()) + "\nPD: " + to_string(gracz->printExp()) + "/" + to_string(gracz->printExpToLv()));
}
void Game::attackRight(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch){
	info.setString(atack(gracz, NPCPlayers, whoIs(make_pair(gracz->getPosition().first + 1, gracz->getPosition().second)), window));
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	level.setString("Poziom: " + to_string(gracz->printLvl()) + "\nPD: " + to_string(gracz->printExp()) + "/" + to_string(gracz->printExpToLv()));
}
void Game::attackRightTop(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch){
	info.setString(atack(gracz, NPCPlayers, whoIs(make_pair(gracz->getPosition().first + 1, gracz->getPosition().second - 1)), window));
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	level.setString("Poziom: " + to_string(gracz->printLvl()) + "\nPD: " + to_string(gracz->printExp()) + "/" + to_string(gracz->printExpToLv()));
}
void Game::attackRightDown(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch){
	info.setString(atack(gracz, NPCPlayers, whoIs(make_pair(gracz->getPosition().first + 1, gracz->getPosition().second + 1)), window));
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	level.setString("Poziom: " + to_string(gracz->printLvl()) + "\nPD: " + to_string(gracz->printExp()) + "/" + to_string(gracz->printExpToLv()));
}
void Game::attackTop(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch){
	info.setString(atack(gracz, NPCPlayers, whoIs(make_pair(gracz->getPosition().first, gracz->getPosition().second - 1)), window));
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	level.setString("Poziom: " + to_string(gracz->printLvl()) + "\nPD: " + to_string(gracz->printExp()) + "/" + to_string(gracz->printExpToLv()));
}
void Game::attackDown(Player* gracz, vector<NPC*>& list, Text& info, Text& level, Text& ruch){
	info.setString(atack(gracz, NPCPlayers, whoIs(make_pair(gracz->getPosition().first, gracz->getPosition().second + 1)), window));
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	level.setString("Poziom: " + to_string(gracz->printLvl()) + "\nPD: " + to_string(gracz->printExp()) + "/" + to_string(gracz->printExpToLv()));
}

void Game::addNPCsFromFile(vector<NPC*>& listaGraczy, string filename){
	std::ifstream nowyPlik;
	nowyPlik.open(filename);
	string read;
	while (!nowyPlik.eof()){
		std::getline(nowyPlik, read);
		int first, second, isArcher;
		std::istringstream sent(read);
		sent >> isArcher;
		sent >> first;
		sent >> second;
		addNPC(NPCPlayers, make_pair(first, second), isArcher);
	}
}

void Game::setMap(Player* gracz, RenderWindow& okno, Map& mapa, bool created, int left, int right, int top, int down, vector<printSprite>& obrazy){
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 24; j++){
			if (i > left && i < right && j > top && j < down){
				obrazy.emplace_back(trawa.printTerrain(), pair<int, int>(30 * i, 30 * j));
			}
			else {
				obrazy.emplace_back(gory.printTerrain(), pair<int, int>(30 * i, 30 * j));
				if (!created)
				mapa.addPosition(make_pair(i, j));
			}
		}
	}
	if (!created){
		gracz->setPosition(15, 3, mapa);
		addNPCsFromFile(NPCPlayers, "enemy.txt");
		/*addNPC(NPCPlayers, make_pair(12, 8), 0);*/
	}
}

void Game::endPlayerTurn(RenderWindow& window, Player* gracz, vector<NPC*>& list, bool endTurn, vector<printSprite>& obrazy, Text& ruch, Sprite& hpBar, string& hp, Text& printHpLine){
	//setMap(gracz, window, mapa, 1, 2, 20, 2, 20, obrazy);
	gracz->setCrossedMove();
	for (auto& players : list){
		players->printIcon().setPosition(30 * players->getPosition().first, 30 * players->getPosition().second);
	}
	gracz->printIcon().setPosition(30 * gracz->getPosition().first, 30 * gracz->getPosition().second);
	gracz->setLeftMove();
	ruch.setString(L"Pozosta³o " + to_string(gracz->printLeftMove()));
	hpBar.setTexture(gracz->getHp().printTexture());
	hp = (to_string(gracz->getHp().printHP()) + "/" + to_string(gracz->getHp().printMaxHP()));
	printHpLine.setString(hp + "\n" + to_string(gracz->printAC()) + "\n" + to_string(gracz->printBasicAttack()) + "/" + to_string(gracz->printDistanceAttack()) + "\n" + to_string(gracz->printSpeed()));
	//info.setString(""); -> jakbym chcia³ skasowaæ linijkê 
	//koniec zestawu
	endTurn = false;
}

void Game::setMapFormFile(Player* gracz, RenderWindow& okno, Map& mapa, bool created, vector<printSprite>& obrazy, string filename){
	std::ifstream nowyPlik;
	nowyPlik.open(filename);
	string read;
	std::getline(nowyPlik, read);
	int left, rigth, top, down;
	std::istringstream sent(read);
	sent >> left;
	sent >> rigth;
	sent >> top;
	sent >> down;
	setMap(gracz, okno, mapa, 0, left, rigth, top, down, obrazy);
}

void Game::gamePlay(Player* Gracz) {

	bg.setTexture(background4);
	Color green(103, 190, 75);
	vector<printSprite> buttonImg;
	vector<printText> button;
	/*setMap(Gracz, window, mapa, 0, 2, 20, 2, 20, buttonImg);*/
	setMapFormFile(Gracz, window, mapa, 0, buttonImg, "map.txt");

	Gracz->printAvatar().setScale(0.65, 0.65);
	buttonImg.emplace_back(Gracz->printAvatar(), pair<int, int>(770, 70));

	string s = Gracz->printStr();
	string d = Gracz->printDex();
	string c = Gracz->printCon();
	string i = Gracz->printInt();
	string w = Gracz->printWis();
	string ch = Gracz->printCha();
	string className = Gracz->printClassName();
	string raseName = Gracz->printRaseName();
	string name = Gracz->printName();
	string hp = (to_string(Gracz->getHp().printHP()) + "/" + to_string(Gracz->getHp().printMaxHP()));
	string ac = (to_string(Gracz->printAC()));
	sf::String distance = Gracz->getSecondWeapon().printName() + " " + to_string(Gracz->getSecondWeapon().printMissles()) + " poc. " + to_string(Gracz->getSecondWeapon().printRange()) + "m\n1k" + to_string(Gracz->getSecondWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getSecondWeapon().printCr()) + "/" + Gracz->getSecondWeapon().printCrRg();
	if (Gracz->getSecondWeapon().printName() == "Brak broni dystansowej")
		distance = Gracz->getSecondWeapon().printName();
	sf::String shield = "+" + to_string(Gracz->getShield().getAC()) + " KP";
	if (Gracz->getShield().getAC() == 0)
		shield = "";
	sf::String armour = "+" + to_string(Gracz->getArmour().getAC()) + " KP";
	if (Gracz->getArmour().getAC() == 0)
		armour = "";

	Text level("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()), font, 22);
	level.setPosition(940, 180);
	level.setColor(green);

	button.emplace_back(name, font, green, 28, pair<int, int>(780, 40));
	button.emplace_back("PW:\nKP:\nAtak: \nPr", font, green, 22, pair<int, int>(940, 80));

	Text printHpLine(hp + "\n" + ac + "\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n" + to_string(Gracz->printSpeed()), font, 22);
	printHpLine.setColor(green);
	printHpLine.setPosition(1000, 80);

	Sprite hpBar(Gracz->getHp().printSprite());
	hpBar.setPosition(940, 40);

	button.emplace_back(L"S: \nZr: \nWtr: \nInt: \nRz: \nCh: \n\nWytr: \nRef: \nWola:", font, green, 22, pair<int, int>(1120, 50));
	button.emplace_back(s + "\n" + d + "\n" + c + "\n" + i + "\n" + w + "\n" + ch + "\n\n   " + to_string(Gracz->printSTFor()) + "\n   " + to_string(Gracz->printSTRef()) + "\n   " + to_string(Gracz->printSTWl()), font, green, 22, pair<int, int>(1180, 50));
	button.emplace_back(L"Zmieñ broñ", font, green, 22, pair<int, int>(1120, 360), Gracz, Orders::ChangeWeapon);
	button.emplace_back(L"Wyjœcie", font, green, 28, pair<int, int>(1120, 650), GameState::END);

	Sprite weapon(Gracz->getMainWeapon().printSprite());
	weapon.setPosition(780, 270);
	Text weapTx(Gracz->getMainWeapon().printName() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, 24);
	weapTx.setPosition(855, 280);
	weapTx.setColor(green);
	Sprite sh(Gracz->getShield().printSprite());
	sh.setPosition(780, 360);
	Text shieldTx(Gracz->getShield().printName() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, 24);
	shieldTx.setPosition(855, 360);
	shieldTx.setColor(green);

	Sprite secWeap(Gracz->getSecondWeapon().printSprite());
	secWeap.setPosition(780, 270);
	Text secWeapTx(Gracz->getSecondWeapon().printName() + " " + to_string(Gracz->getSecondWeapon().printMissles()) + " poc. " + to_string(Gracz->getSecondWeapon().printRange()) + "m\n1k" + to_string(Gracz->getSecondWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getSecondWeapon().printCr()) + "/" + Gracz->getSecondWeapon().printCrRg(), font, 24);
	secWeapTx.setPosition(855, 280);
	secWeapTx.setColor(green);

	Text info(L"", font, 22);
	info.setPosition(960, 450);
	info.setColor(green);

	Texture end,top,down,left,leftTop,leftDown,right,rightTop,rightDown;
	Sprite endSprite, topSprite, downSprite, leftSprite, leftDownSprite, leftTopSprite, rightSprite, rightTopSprite, rightDownSprite;

	addPhoto(endSprite, end, "end.png");
	addPhoto(topSprite, top, "top.png");
	addPhoto(downSprite, down, "down.png");
	addPhoto(leftSprite, left, "left.png");
	addPhoto(leftTopSprite, leftTop, "left_top.png");
	addPhoto(leftDownSprite, leftDown, "left_down.png");
	addPhoto(rightSprite, right, "right.png");
	addPhoto(rightTopSprite, rightTop, "right_top.png");
	addPhoto(rightDownSprite, rightDown, "right_down.png");

	buttonImg.emplace_back(leftSprite, pair<int, int>(800, 500), Gracz, Orders2::Left);
	buttonImg.emplace_back(leftTopSprite, pair<int, int>(800, 450), Gracz, Orders2::LeftTop);
	buttonImg.emplace_back(leftDownSprite, pair<int, int>(800, 550), Gracz, Orders2::LeftDown);
	buttonImg.emplace_back(topSprite, pair<int, int>(850, 450), Gracz, Orders2::Top);
	buttonImg.emplace_back(endSprite, pair<int, int>(850, 500), Gracz, Orders2::EndTurn);
	buttonImg.emplace_back(downSprite, pair<int, int>(850, 550), Gracz, Orders2::Down);
	buttonImg.emplace_back(rightSprite, pair<int, int>(900, 500), Gracz, Orders2::Right);
	buttonImg.emplace_back(rightTopSprite, pair<int, int>(900, 450), Gracz, Orders2::RightTop);
	buttonImg.emplace_back(rightDownSprite, pair<int, int>(900, 550), Gracz, Orders2::RightDown);

	Text ruch(L"Pozosta³o " + to_string(Gracz->printLeftMove()), font, 22);
	ruch.setColor(green);
	ruch.setPosition(800, 620);


	bool endTurn = true;
	printText* hoverPrintText = nullptr;
	printSprite* hoverSprite = nullptr;
	while (state == GameState::GAME)
	{
		if (endTurn){
			endPlayerTurn(window, Gracz, NPCPlayers, endTurn, buttonImg, ruch, hpBar, hp, printHpLine);
			endTurn = false;
		}

		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		hoverPrintText = nullptr;
		hoverSprite = nullptr;

		for (auto& button : button){
			if ((button.GetText().getGlobalBounds().contains(mouse)) && (button.GetState() != GameState::UNKNOWN || button.getOrder() == Orders::ChangeWeapon))
			{
				button.GetText().setStyle(Text::Underlined);
				hoverPrintText = &button;}
			else
			{
				button.GetText().setStyle(Text::Regular);
				button.GetText().setColor(Color::Black);}
		}
		for (auto& button : buttonImg){
			if (button.GetSprite().getGlobalBounds().contains(mouse)){
				hoverSprite = &button;
			}
		}
		while (window.pollEvent(event) && state == GameState::GAME)
		{
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (hoverPrintText)
				{
					if (hoverPrintText->GetState() != GameState::UNKNOWN)
						state = hoverPrintText->GetState();
					//else if (hoverPrintText->getOrder() == Orders::ChangeWeapon){ // kiedyœ bêdzie mo¿na u¿ywaæ ³uku, ale na razie to by nic nie da³o
					//	Gracz->changeWeapon();
					//	endTurn = true;
					//}
				}
				if (hoverSprite){
					if (hoverSprite->getOrder() == Orders2::Left){
						if(Gracz->printLeftMove() > 0 && Gracz->getPosition().first > 0 && mapa.isEmpty(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second))){
						Gracz->moveLeft(mapa, ruch);}
						else if ((hoverSprite->getOrder() == Orders2::Left) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second))){
							attackLeft(Gracz, NPCPlayers, info, level, ruch);}}
					else if (hoverSprite->getOrder() == Orders2::Right){
						if (Gracz->printLeftMove() > 0 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second)))	{
							Gracz->moveRight(mapa, ruch);}
						else if ((hoverSprite->getOrder() == Orders2::Right) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second))){
							attackRight(Gracz, NPCPlayers, info, level, ruch);}}
					else if (hoverSprite->getOrder() == Orders2::LeftDown){
						if (((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().first > 0 && Gracz->getPosition().second<23 && mapa.isEmpty(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second + 1)))	{
							Gracz->moveLeftDown(mapa, ruch);}
						else if ((hoverSprite->getOrder() == Orders2::LeftDown) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second + 1))){
							attackLeftDown(Gracz, NPCPlayers, info, level, ruch);}}
					else if (hoverSprite->getOrder() == Orders2::RightDown){
						if (((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().second < 23 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second + 1)))	{
							Gracz->moveRightDown(mapa, ruch);}
						else if ((hoverSprite->getOrder() == Orders2::RightDown) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second + 1))){
							attackRightDown(Gracz, NPCPlayers, info, level, ruch);}	}
					else if (hoverSprite->getOrder() == Orders2::LeftTop){
					if (((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().first > 0 && Gracz->getPosition().second > 0 && mapa.isEmpty(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second - 1)))	{
						Gracz->moveLeftTop(mapa, ruch);	}
					else if ((hoverSprite->getOrder() == Orders2::LeftTop) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second - 1))){
						attackLeftTop(Gracz, NPCPlayers, info, level, ruch);}}
					else if (hoverSprite->getOrder() == Orders2::RightTop){
						if (((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().second > 0 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second - 1)))	{
							Gracz->moveRightTop(mapa, ruch);}
						else if ((hoverSprite->getOrder() == Orders2::RightTop) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second - 1))){
							attackRightTop(Gracz, NPCPlayers, info, level, ruch);}}
					else if (hoverSprite->getOrder() == Orders2::Top){
						if (Gracz->printLeftMove() > 0 && Gracz->getPosition().second > 0 && mapa.isEmpty(make_pair(Gracz->getPosition().first, Gracz->getPosition().second - 1)))	{
							Gracz->moveTop(mapa, ruch);}
						else if ((hoverSprite->getOrder() == Orders2::Top) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first, Gracz->getPosition().second - 1))){
							attackTop(Gracz, NPCPlayers, info, level, ruch);}}
					else if (hoverSprite->getOrder() == Orders2::Down){
						if (Gracz->printLeftMove() > 0 && Gracz->getPosition().second < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first, Gracz->getPosition().second + 1)))	{
							Gracz->moveDown(mapa, ruch);}
						else if ((hoverSprite->getOrder() == Orders2::Down) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first, Gracz->getPosition().second + 1))){
							attackDown(Gracz, NPCPlayers, info, level, ruch);}}
					else if ((hoverSprite->getOrder() == Orders2::EndTurn))	{
						endTurn = true;
						for (auto& players : NPCPlayers){
							info.setString(NPCturn(Gracz, players, window));
						}						
					}
				}
			}
			window.clear();
			window.draw(bg);
			for (auto &button : button)
			{
				button.GetText().setColor(button.setColor());
				window.draw(button.GetText());
			}
			for (auto& button : buttonImg){
				window.draw(button.GetSprite());
			}
			for (auto& players : NPCPlayers){
				window.draw(players->printIcon());
			}
			window.draw(Gracz->printIcon());
			if (Gracz->getHp().printHP() <= 0){
				state = GameState::LOSE;
				for (auto& players : NPCPlayers){
					delete players;
				}
				delete Gracz;
				delete NPCposition;
			}
			if (NPCPlayers.size() == 0){
				state = GameState::WIN;
				delete Gracz;
				for (auto& players : NPCPlayers){
					delete players;
				}
				delete NPCposition;
			}
			window.draw(hpBar);
			window.draw(printHpLine);
			window.draw(level);
			window.draw(info);
			window.draw(ruch);
			if (Gracz->isMeleeWeapon()){
				window.draw(weapon);
				window.draw(weapTx);
				window.draw(sh);
				window.draw(shieldTx);
			}
			else{
				window.draw(secWeap);
				window.draw(secWeapTx);
			}
			window.display();
		}
	}
}

void Game::winGame() {
		bg.setTexture(background2);
		vector<printText> button;
		button.emplace_back(L"Wygra³eœ", font, Color::Black, 48, pair<int, int>(300, 20));
		button.emplace_back(L"WyjdŸ z gry", font, Color::Black, 36, pair<int, int>(700, 500), GameState::END);

		printText* hoverPrintText = nullptr;
		while (state == GameState::WIN)
		{
			Vector2f mouse(Mouse::getPosition(window));
			Event event;
			hoverPrintText = nullptr;

			for (auto& button : button)
			if ((button.GetText().getGlobalBounds().contains(mouse)) && (button.GetState() != GameState::UNKNOWN))
			{
				button.GetText().setStyle(Text::Underlined);
				hoverPrintText = &button;
			}
			else
			{
				button.GetText().setStyle(Text::Regular);
			}

			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverPrintText)
				{
					if (hoverPrintText->GetState() != GameState::UNKNOWN)
						state = hoverPrintText->GetState();
					break;
				}
			}
			window.clear();
			window.draw(bg);
			for (auto &button : button)
			{
				button.GetText().setColor(button.setColor());
				window.draw(button.GetText());
			}
			window.display();
		}
}

void Game::loseGame() {
	bg.setTexture(background2);
	vector<printText> button;
	button.emplace_back(L"Przegra³eœ", font, Color::Black, 48, pair<int, int>(300, 20));
	button.emplace_back(L"WyjdŸ z gry", font, Color::Black, 36, pair<int, int>(700, 500), GameState::END);

	printText* hoverPrintText = nullptr;
	while (state == GameState::LOSE)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		hoverPrintText = nullptr;

		for (auto& button : button)
		if ((button.GetText().getGlobalBounds().contains(mouse)) && (button.GetState() != GameState::UNKNOWN))
		{
			button.GetText().setStyle(Text::Underlined);
			hoverPrintText = &button;
		}
		else
		{
			button.GetText().setStyle(Text::Regular);
		}

		while (window.pollEvent(event))
		{
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverPrintText)
			{
				if (hoverPrintText->GetState() != GameState::UNKNOWN)
					state = hoverPrintText->GetState();
				break;
			}
		}
		window.clear();
		window.draw(bg);
		for (auto &button : button)
		{
			button.GetText().setColor(button.setColor());
			window.draw(button.GetText());
		}
		window.display();
	}
}