#include "game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Windows.h>
#include <string>
#include "player.h"
#include "printText.h"
#include "printSprite.h"
#include "Map.h"

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
		case GameState::MENU2:
			newPlayer();
			break;
		case GameState::MENU2_a:{
			//khelgar(Gracz);
			Player* Gracz = new Player(playerClass::fighter, rase::dwarf, Ability(15), Ability(12), Ability(14), Ability(10), Ability(10), Ability(10), Level(0), Armor(), true, "Khelgar");
			Gracz->setMainWeapon(WeaponCollection::SmallAxe);
			Gracz->setDistanceWeapon(WeaponCollection::Crossbow);
			Gracz->setShield(WeaponCollection::LightShield); //logicial error, TH weapon with shield is impossible
			Gracz->setArmour(WeaponCollection::MailShirt);
			printPlayer(Gracz);
			gamePlay(Gracz);
		}
			break;
		case GameState::MENU2_b:{
			Player* Gracz =  new Player(playerClass::wizard, rase::human, Ability(8), Ability(12), Ability(10), Ability(16), Ability(14), Ability(10), Level(0), Armor(), true, "Rodger");
			Gracz->setMainWeapon(WeaponCollection::Fist); //trolololo i tak nie mo�e
			Gracz->setDistanceWeapon(WeaponCollection::Slingshot);
			Gracz->setArmour(WeaponCollection::LeatherArmor);//trololo i tak nie mo�e
			Gracz->setShield(WeaponCollection::LightShield);
			printPlayer(Gracz);
			gamePlay(Gracz);
		}
			break;
		case GameState::MENU2_c:{
			Player* Gracz = new Player(playerClass::hunter, rase::elf, Ability(15), Ability(14), Ability(12), Ability(10), Ability(10), Ability(10), Level(0), Armor(), false, "Tharwen");
			Gracz->setMainWeapon(WeaponCollection::Longsword);
			Gracz->setDistanceWeapon(WeaponCollection::Longbow);
			Gracz->setArmour(WeaponCollection::LeatherArmor);
			printPlayer(Gracz);
			gamePlay(Gracz);
		}
			break;
		}
	}
}


void Game::menu()
{
	bg.setTexture(background2);
	vector<printText> button;
	button.emplace_back(L"Witaj dzielny �mia�ku, \nOd Twojego zadania\n  Zale�� losy\n  nas wszystkich", font, Color::Black, 48, pair<int, int>(300, 20));
	button.emplace_back(L"Nowa Gra", font, Color::Black, 36, pair<int, int>(650, 300), GameState::MENU2);
	button.emplace_back(L"Graj dalej", font, Color::Black, 36, pair<int, int>(650, 350));
	button.emplace_back(L"Wyjd� z gry", font, Color::Black, 36, pair<int, int>(700, 500), GameState::END);

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
	button.emplace_back(L"Wybierz kt�rego� z bohater�w", font, Color::Black, 48, pair<int, int>(120, 20));
	button.emplace_back(L"Khelgar, krasnolud wojownik", font, Color::Black, 32, pair<int, int>(120, 200), GameState::MENU2_a);
	button.emplace_back(L"Rodger, mag cz�owiek", font, Color::Black, 32, pair<int, int>(120, 260), GameState::MENU2_b);
	button.emplace_back(L"Th�rwen, elfka tropiciel", font, Color::Black, 32, pair<int, int>(120, 320), GameState::MENU2_c);
	button.emplace_back(L"Powr�t", font, Color::Black, 32, pair<int, int>(120, 600), GameState::MENU);

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
	sf::String distance = Gracz->getSecondWeapon().printWeapon() + " poc. " + to_string(Gracz->getSecondWeapon().printMissles()) + L" zasi�g " + to_string(Gracz->getSecondWeapon().printRange()) + "\n1k" + to_string(Gracz->getSecondWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getSecondWeapon().printCr()) + "/" + Gracz->getSecondWeapon().printCrRg();
	if (Gracz->getSecondWeapon().printWeapon() == "Brak broni dystansowej")
		distance = Gracz->getSecondWeapon().printWeapon();
	sf::String shield = "+" + to_string(Gracz->getShield().getAC()) + " KP";
	if (Gracz->getShield().getAC() == 0)
		shield = "";
	sf::String armour = "+" + to_string(Gracz->getArmour().getAC()) + " KP";
	if (Gracz->getArmour().getAC() == 0)
		armour = "";

	Gracz->setPosition(15, 3, mapa);

	vector<printText> button;
	button.emplace_back(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Gracz->printLvl()) + "\n\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()), font, gold, 28, pair<int, int>(260, 50));
	button.emplace_back(hp + "\n\n" + L"Premia do ataku: \n\nPr�dko�� \n\nWytrwa�o��: \n\nRefleks: \n\nWola: ", font, gold, 22, pair<int, int>(490, 50));
	button.emplace_back(ac + "\n\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n\n" + to_string(Gracz->printSpeed()) + "\n\n" + to_string(Gracz->printSTFor()) + "\n\n" + to_string(Gracz->printSTRef()) + "\n\n" + to_string(Gracz->printSTWl()), font, gold, 22, pair<int, int>(720, 50));
	button.emplace_back(L"Si�a: \n\nZr�czno��: \n\nWytrzyma�o��: \n\nIntelekt: \n\nRozs�dek: \n\nCharyzma: ", font, gold, 22, pair<int, int>(900, 50));
	button.emplace_back(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, gold, 22, pair<int, int>(1130, 50));
	button.emplace_back(Gracz->getMainWeapon().printWeapon() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, gold, 24, pair<int, int>(125, 370));
	button.emplace_back(distance, font, gold, 24, pair<int, int>(125, 470));
	button.emplace_back(Gracz->getShield().printShield() + "\n" + shield, font, gold, 22, pair<int, int>(550, 370));
	button.emplace_back(Gracz->getArmour().printArmour() + "\n" + armour, font, gold, 22, pair<int, int>(550, 470));
	button.emplace_back(L"Powr�t", font, gold, 28, pair<int, int>(200, 600), GameState::MENU2);
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
		NPC* enemy = new NPC(true, Ability(15), Ability(12), Ability(14), Ability(10), Ability(10), Ability(10), Level(0), Armor(), "NPC1");
		enemy->setMainWeapon(WeaponCollection::Dagger);
		enemy->setDistanceWeapon(WeaponCollection::Bow);
		enemy->setArmour(WeaponCollection::LeatherArmor);
		enemy->setPosition(location.first, location.second, mapa);
		listaGraczy.emplace_back(enemy);
	}
	else{
		NPC* enemy = new NPC(false, Ability(15), Ability(12), Ability(14), Ability(10), Ability(10), Ability(10), Level(0), Armor(),  "NPC2");
		enemy->setMainWeapon(WeaponCollection::Longsword);
		enemy->setArmour(WeaponCollection::LeatherArmor);
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
			enemy.erase(enemy.begin() + number);
			killThemAll = "\nZabito wroga!";
			}
	player->endTurn();
	if (roll >= player->getMainWeapon().printCrRange())
	return(L"Wyrzucono: " + to_string(roll) + " + " + to_string(player->printBasicAttack()) + L"\nTrafienie krytyczne!\n\nZadano " + to_string(damage) + L" obra�e�" + killThemAll);
	
	else
		return(L"Wyrzucono: " + to_string(roll) + " + " + to_string(player->printBasicAttack()) + L"\nTrafienie!\n\nZadano " + to_string(damage) + L" obra�e�" + killThemAll);
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
	enemy->setLeftMove();
	enemy->setCrossedMove();
	while (enemy->printLeftMove() > 0){
		if (wayToPlayer(player, enemy).first < -1 || wayToPlayer(player, enemy).first > 1 || wayToPlayer(player, enemy).second < -1 || wayToPlayer(player, enemy).second > 1){
			if ((wayToPlayer(player, enemy).first  < -1 && wayToPlayer(player, enemy).second  > 1) && mapa.isEmpty(make_pair(enemy->getPosition().first + 1, enemy->getPosition().second - 1))){//prawo g�ra
				mapa.freePosition(enemy->getPosition());
				enemy->isCrossedMove();
				enemy->setPosition(enemy->getPosition().first + 1, enemy->getPosition().second - 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).first > 1 && wayToPlayer(player, enemy).second > 1) && mapa.isEmpty(make_pair(enemy->getPosition().first - 1, enemy->getPosition().second - 1))){ //lewo g�ra
				mapa.freePosition(enemy->getPosition());
				enemy->isCrossedMove();
				enemy->setPosition(enemy->getPosition().first - 1, enemy->getPosition().second - 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).first < -1 && wayToPlayer(player, enemy).second  < -1) && mapa.isEmpty(make_pair(enemy->getPosition().first + 1, enemy->getPosition().second + 1))){ //prawo d�
				mapa.freePosition(enemy->getPosition());
				enemy->isCrossedMove();
				enemy->setPosition(enemy->getPosition().first + 1, enemy->getPosition().second + 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).first  > 1 && wayToPlayer(player, enemy).second  < -1) && mapa.isEmpty(make_pair(enemy->getPosition().first + 1, enemy->getPosition().second + 1))){ //lewo g�ra
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
			else if ((wayToPlayer(player, enemy).second  > 1) && mapa.isEmpty(make_pair(enemy->getPosition().first, enemy->getPosition().second - 1))) {//g�ra
				mapa.freePosition(enemy->getPosition());
				enemy->setPosition(enemy->getPosition().first, enemy->getPosition().second - 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else if ((wayToPlayer(player, enemy).second < -1) && mapa.isEmpty(make_pair(enemy->getPosition().first, enemy->getPosition().second + 1))) {//d�
				mapa.freePosition(enemy->getPosition());
				enemy->setPosition(enemy->getPosition().first, enemy->getPosition().second + 1, mapa);
				enemy->printIcon().setPosition(30 * enemy->getPosition().first, 30 * enemy->getPosition().second);
			}
			else {
				enemy->setPosition(enemy->getPosition().first, enemy->getPosition().second, mapa);
				mapa.freePosition(enemy->getPosition());
			}
			out = (L"Przeciwnik si� ruszy�");
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
				out = (L"Wr�g wyrzuci�: " + to_string(roll) + " + " + to_string(enemy->printBasicAttack()) + L"\nTrafienie krytyczne!\n\nZadano " + to_string(damage) + L" obra�e�" + killThemAll);
		
				else
				out = (L"Wr�g wyrzuci�: " + to_string(roll) + " + " + to_string(enemy->printBasicAttack()) + L"\nTrafienie!\n\nZadano " + to_string(damage) + L" obra�e�" + killThemAll);

				player->endTurn();
				}
			else
				out = (L"Wr�g wyrzuci�: " + to_string(roll) + " + " + to_string(player->printBasicAttack()) + "\nNie trafiono!");
				enemy->endTurn();
		}
	}
	return out;
}

void::Game::gamePlay(Player* Gracz) {

	addNPC(NPCPlayers, make_pair(12, 8), 0);
//	addNPC(NPCPlayers, make_pair(12, 10), 0);
//	addNPC(NPCPlayers, make_pair(5, 5), 0);

	bg.setTexture(background4);
	Color green(103, 190, 75);
	vector<printSprite> buttonImg;
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
	sf::String distance = Gracz->getSecondWeapon().printWeapon() + " " + to_string(Gracz->getSecondWeapon().printMissles()) + " poc. " + to_string(Gracz->getSecondWeapon().printRange()) + "m\n1k" + to_string(Gracz->getSecondWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getSecondWeapon().printCr()) + "/" + Gracz->getSecondWeapon().printCrRg();
	if (Gracz->getSecondWeapon().printWeapon() == "Brak broni dystansowej")
		distance = Gracz->getSecondWeapon().printWeapon();
	sf::String shield = "+" + to_string(Gracz->getShield().getAC()) + " KP";
	if (Gracz->getShield().getAC() == 0)
		shield = "";
	sf::String armour = "+" + to_string(Gracz->getArmour().getAC()) + " KP";
	if (Gracz->getArmour().getAC() == 0)
		armour = "";


	vector<printText> button;

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
	button.emplace_back(L"Zmie� bro�", font, green, 22, pair<int, int>(1120, 360), Gracz, Orders::ChangeWeapon);
	button.emplace_back(L"Wyj�cie", font, green, 28, pair<int, int>(1120, 650), GameState::END);

	Sprite weapon(Gracz->getMainWeapon().printSprite());
	weapon.setPosition(780, 270);
	Text weapTx(Gracz->getMainWeapon().printWeapon() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, 24);
	weapTx.setPosition(855, 280);
	weapTx.setColor(green);

	Sprite sh(Gracz->getShield().printSprite());
	sh.setPosition(780, 360);
	Text shieldTx(Gracz->getShield().printShield() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, 24);
	shieldTx.setPosition(855, 360);
	shieldTx.setColor(green);

	Sprite secWeap(Gracz->getSecondWeapon().printSprite());
	secWeap.setPosition(780, 270);
	Text secWeapTx(Gracz->getSecondWeapon().printWeapon() + " " + to_string(Gracz->getSecondWeapon().printMissles()) + " poc. " + to_string(Gracz->getSecondWeapon().printRange()) + "m\n1k" + to_string(Gracz->getSecondWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getSecondWeapon().printCr()) + "/" + Gracz->getSecondWeapon().printCrRg(), font, 24);
	secWeapTx.setPosition(855, 280);
	secWeapTx.setColor(green);

	Text info(L"", font, 22);
	info.setPosition(960, 450);
	info.setColor(green);
	window.draw(info);

	Texture end;
	end.loadFromFile("end.png");
	Sprite endSprite;
	endSprite.setTexture(end);
	Texture top;
	top.loadFromFile("top.png");
	Sprite topSprite;
	topSprite.setTexture(top);
	Texture down;
	down.loadFromFile("down.png");
	Sprite downSprite;
	downSprite.setTexture(down);
	Texture left;
	left.loadFromFile("left.png");
	Sprite leftSprite;
	leftSprite.setTexture(left);
	Texture leftTop;
	leftTop.loadFromFile("left_top.png");
	Sprite leftTopSprite;
	leftTopSprite.setTexture(leftTop);
	Texture leftDown;
	leftDown.loadFromFile("left_down.png");
	Sprite leftDownSprite;
	leftDownSprite.setTexture(leftDown);
	Texture right;
	right.loadFromFile("right.png");
	Sprite rightSprite;
	rightSprite.setTexture(right);
	Texture rightTop;
	rightTop.loadFromFile("right_top.png");
	Sprite rightTopSprite;
	rightTopSprite.setTexture(rightTop);
	Texture rightDown;
	rightDown.loadFromFile("right_down.png");
	Sprite rightDownSprite;
	rightDownSprite.setTexture(rightDown);

	buttonImg.emplace_back(leftSprite, pair<int, int>(800, 500), Gracz, Orders2::Left);
	buttonImg.emplace_back(leftTopSprite, pair<int, int>(800, 450), Gracz, Orders2::LeftTop);
	buttonImg.emplace_back(leftDownSprite, pair<int, int>(800, 550), Gracz, Orders2::LeftDown);
	buttonImg.emplace_back(topSprite, pair<int, int>(850, 450), Gracz, Orders2::Top);
	buttonImg.emplace_back(endSprite, pair<int, int>(850, 500), Gracz, Orders2::EndTurn);
	buttonImg.emplace_back(downSprite, pair<int, int>(850, 550), Gracz, Orders2::Down);
	buttonImg.emplace_back(rightSprite, pair<int, int>(900, 500), Gracz, Orders2::Right);
	buttonImg.emplace_back(rightTopSprite, pair<int, int>(900, 450), Gracz, Orders2::RightTop);
	buttonImg.emplace_back(rightDownSprite, pair<int, int>(900, 550), Gracz, Orders2::RightDown);

	Text ruch(L"Pozosta�o " + to_string(Gracz->printLeftMove()), font, 22);
	ruch.setColor(green);
	ruch.setPosition(800, 620);

	Grass trawka;
	Hill gory;
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 24; j++){
			if (i > 4 && i < 20 && j > 2 && j < 18){
				buttonImg.emplace_back(trawka.printTerrain(), pair<int, int>(30 * i, 30 * j));
			}
			else {
				buttonImg.emplace_back(gory.printTerrain(), pair<int, int>(30 * i, 30 * j));
				mapa.addPosition(make_pair(i, j));
			}
		}
	}

	bool endTurn = true;
	printText* hoverPrintText = nullptr;
	printSprite* hoverSprite = nullptr;
	while (state == GameState::GAME)
	{
		if (endTurn){

			//zestaw rzeczy do wykonania przed tur� //
			for (int i = 0; i < 24; i++){
				for (int j = 0; j < 24; j++){
					if (i > 4 && i < 20 && j > 2 && j < 18){
						buttonImg.emplace_back(trawka.printTerrain(), pair<int, int>(30 * i, 30 * j));
					}
					else
						buttonImg.emplace_back(gory.printTerrain(), pair<int, int>(30 * i, 30 * j));
				}
			}

			Gracz->setCrossedMove();

			for (auto& players : NPCPlayers){
				players->printIcon().setPosition(30 * players->getPosition().first, 30 * players->getPosition().second);
			}
			Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);

			Gracz->setLeftMove();
			ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
			hpBar.setTexture(Gracz->getHp().printTexture());
			hp = (to_string(Gracz->getHp().printHP()) + "/" + to_string(Gracz->getHp().printMaxHP()));
			printHpLine.setString(hp + "\n" + ac + "\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n" + to_string(Gracz->printSpeed()));
			//info.setString("");
			//koniec zestawu

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
				hoverPrintText = &button;
			}
			else
			{
				button.GetText().setStyle(Text::Regular);
				button.GetText().setColor(Color::Black);
			}
		}

		for (auto& button : buttonImg){
			if (button.GetSprite().getGlobalBounds().contains(mouse)){
				hoverSprite = &button;
			}
		}


		while (window.pollEvent(event))
		{

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (hoverPrintText)
				{
					if (hoverPrintText->GetState() != GameState::UNKNOWN)
						state = hoverPrintText->GetState();
					else if (hoverPrintText->getOrder() == Orders::ChangeWeapon){
						Gracz->changeWeapon();
						endTurn = true;
					}
				}

				//
				if (hoverSprite){
					if (hoverSprite->getOrder() == Orders2::Left){
						if(Gracz->printLeftMove() > 0 && Gracz->getPosition().first > 0 && mapa.isEmpty(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second))){
						mapa.freePosition(Gracz->getPosition());
						Gracz->setPosition(Gracz->getPosition().first - 1, Gracz->getPosition().second, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
						}
						else if ((hoverSprite->getOrder() == Orders2::Left) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second))){
							info.setString(atack(Gracz, NPCPlayers, whoIs(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second)), window));
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
							level.setString("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()));
						}
					}
					else if (hoverSprite->getOrder() == Orders2::Right){
						if (Gracz->printLeftMove() > 0 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->setPosition(Gracz->getPosition().first + 1, Gracz->getPosition().second, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
						}
						else if ((hoverSprite->getOrder() == Orders2::Right) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second))){
							info.setString(atack(Gracz, NPCPlayers, whoIs(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second)), window));
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
							level.setString("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()));
						}
					}
					else if (hoverSprite->getOrder() == Orders2::LeftDown){
						if (((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().first > 0 && Gracz->getPosition().second<23 && mapa.isEmpty(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second + 1)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->isCrossedMove();
						Gracz->setPosition(Gracz->getPosition().first - 1, Gracz->getPosition().second + 1, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
						}
						else if ((hoverSprite->getOrder() == Orders2::LeftDown) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second + 1))){
							info.setString(atack(Gracz, NPCPlayers, whoIs(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second + 1)), window));
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
							level.setString("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()));
						}
					}
					else if (hoverSprite->getOrder() == Orders2::RightDown){
						if (((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().second < 23 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second + 1)))	{
							mapa.freePosition(Gracz->getPosition());
							Gracz->isCrossedMove();
							Gracz->setPosition(Gracz->getPosition().first + 1, Gracz->getPosition().second + 1, mapa);
							Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
						}
						else if ((hoverSprite->getOrder() == Orders2::RightDown) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second + 1))){
							info.setString(atack(Gracz, NPCPlayers, whoIs(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second + 1)), window));
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
							level.setString("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()));
						}
					}
					else if (hoverSprite->getOrder() == Orders2::LeftTop){
					if (((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().first > 0 && Gracz->getPosition().second > 0 && mapa.isEmpty(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second - 1)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->isCrossedMove();
						Gracz->setPosition(Gracz->getPosition().first - 1, Gracz->getPosition().second - 1, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
					}
					else if ((hoverSprite->getOrder() == Orders2::LeftTop) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second - 1))){
						info.setString(atack(Gracz, NPCPlayers, whoIs(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second - 1)), window));
						ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
						level.setString("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()));
						}
					}
					else if (hoverSprite->getOrder() == Orders2::RightTop){
						if (((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().second > 0 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second - 1)))	{
							mapa.freePosition(Gracz->getPosition());
							Gracz->isCrossedMove();
							Gracz->setPosition(Gracz->getPosition().first + 1, Gracz->getPosition().second - 1, mapa);
							Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
						}
						else if ((hoverSprite->getOrder() == Orders2::RightTop) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second - 1))){
							info.setString(atack(Gracz, NPCPlayers, whoIs(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second - 1)), window));
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
							level.setString("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()));
						}
					}
					else if (hoverSprite->getOrder() == Orders2::Top){
						if (Gracz->printLeftMove() > 0 && Gracz->getPosition().second > 0 && mapa.isEmpty(make_pair(Gracz->getPosition().first, Gracz->getPosition().second - 1)))	{
							mapa.freePosition(Gracz->getPosition());
							Gracz->setPosition(Gracz->getPosition().first, Gracz->getPosition().second - 1, mapa);
							Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
						}
						else if ((hoverSprite->getOrder() == Orders2::Top) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first, Gracz->getPosition().second - 1))){
							info.setString(atack(Gracz, NPCPlayers, whoIs(make_pair(Gracz->getPosition().first, Gracz->getPosition().second - 1)), window));
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
							level.setString("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()));
						}
					}
					else if (hoverSprite->getOrder() == Orders2::Down){
						if (Gracz->printLeftMove() > 0 && Gracz->getPosition().second < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first, Gracz->getPosition().second + 1)))	{
							mapa.freePosition(Gracz->getPosition());
							Gracz->setPosition(Gracz->getPosition().first, Gracz->getPosition().second + 1, mapa);
							Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
						}
						else if ((hoverSprite->getOrder() == Orders2::Down) && Gracz->printLeftMove() > 0 && isEnemy(make_pair(Gracz->getPosition().first, Gracz->getPosition().second + 1))){
							info.setString(atack(Gracz, NPCPlayers, whoIs(make_pair(Gracz->getPosition().first, Gracz->getPosition().second + 1)), window));
							ruch.setString(L"Pozosta�o " + to_string(Gracz->printLeftMove()));
							level.setString("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()));
						}
					}

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
				Sprite deathSprite;
				Texture death;
				death.loadFromFile("death.png");
				deathSprite.setTexture(death);
				window.draw(deathSprite);
			}
			window.draw(hpBar);
			window.draw(printHpLine);
			window.draw(level);
			window.draw(info);
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

			window.draw(ruch);
			window.display();
		}
	}
}