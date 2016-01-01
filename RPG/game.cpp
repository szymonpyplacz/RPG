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
	button.emplace_back(L"Witaj dzielny �mia�ku, \nOd Twojego zadania\n  Zale�� losy\n  nas wszystkich", font, Color::Black, 48, pair<float, float>(300, 20));
	button.emplace_back(L"Nowa Gra", font, Color::Black, 36, pair<float, float>(650, 300), GameState::MENU2);
	button.emplace_back(L"Graj dalej", font, Color::Black, 36, pair<float, float>(650, 350));
	button.emplace_back(L"Wyjd� z gry", font, Color::Black, 36, pair<float, float>(700, 500), GameState::END);

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
	button.emplace_back(L"Wybierz kt�rego� z bohater�w", font, Color::Black, 48, pair<float, float>(120, 20));
	button.emplace_back(L"Khelgar, krasnolud wojownik", font, Color::Black, 32, pair<float, float>(120, 200), GameState::MENU2_a);
	button.emplace_back(L"Rodger, mag cz�owiek", font, Color::Black, 32, pair<float, float>(120, 260), GameState::MENU2_b);
	button.emplace_back(L"Th�rwen, elfka tropiciel", font, Color::Black, 32, pair<float, float>(120, 320), GameState::MENU2_c);
	button.emplace_back(L"Powr�t", font, Color::Black, 32, pair<float, float>(120, 600), GameState::MENU);

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
	Texture wood;
	wood.loadFromFile("belka.gif");
	Sprite woodSprite;
	woodSprite.setTexture(wood);
	vector<printSprite> buttonImg;
	buttonImg.emplace_back(woodSprite, pair<float, float>(430, 35));
	buttonImg.emplace_back(woodSprite, pair<float, float>(820, 35));
	buttonImg.emplace_back(Gracz->printAvatar(), pair<float, float>(45, 40));
	buttonImg.emplace_back(Gracz->getMainWeapon().printSprite(), pair<float, float>(50, 360));
	buttonImg.emplace_back(Gracz->getSecondWeapon().printSprite(), pair<float, float>(50, 460));
	buttonImg.emplace_back(Gracz->getShield().printSprite(), pair<float, float>(470, 360));
	buttonImg.emplace_back(Gracz->getArmour().printSprite(), pair<float, float>(470, 460));
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

	Gracz->setPosition(5, 3);

	vector<printText> button;
	button.emplace_back(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Gracz->printLvl()) + "\n\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()), font, gold, 28, pair<float, float>(260, 50));
	button.emplace_back(hp + "\n\n" + L"Premia do ataku: \n\nPr�dko�� \n\nWytrwa�o��: \n\nRefleks: \n\nWola: ", font, gold, 22, pair<float, float>(490, 50));
	button.emplace_back(ac + "\n\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n\n" + to_string(Gracz->printSpeed()) + "\n\n" + to_string(Gracz->printSTFor()) + "\n\n" + to_string(Gracz->printSTRef()) + "\n\n" + to_string(Gracz->printSTWl()), font, gold, 22, pair<float, float>(720, 50));
	button.emplace_back(L"Si�a: \n\nZr�czno��: \n\nWytrzyma�o��: \n\nIntelekt: \n\nRozs�dek: \n\nCharyzma: ", font, gold, 22, pair<float, float>(900, 50));
	button.emplace_back(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, gold, 22, pair<float, float>(1130, 50));
	button.emplace_back(Gracz->getMainWeapon().printWeapon() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, gold, 24, pair<float, float>(125, 370));
	button.emplace_back(distance, font, gold, 24, pair<float, float>(125, 470));
	button.emplace_back(Gracz->getShield().printShield() + "\n" + shield, font, gold, 22, pair<float, float>(550, 370));
	button.emplace_back(Gracz->getArmour().printArmour() + "\n" + armour, font, gold, 22, pair<float, float>(550, 470));
	button.emplace_back(L"Powr�t", font, gold, 28, pair<float, float>(200, 600), GameState::MENU2);
	button.emplace_back(L"Dalej", font, gold, 28, pair<float, float>(800, 600), GameState::GAME);

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

void::Game::gamePlay(Player* Gracz) {
	bg.setTexture(background4);
	Color green(103, 190, 75);
	//Gracz->getHp().getDmg(1);
	vector<printSprite> buttonImg;
	Gracz->printAvatar().setScale(0.65, 0.65);
	buttonImg.emplace_back(Gracz->printAvatar(), pair<float, float>(770, 70));
	Grass trawka;
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 24; j++){
			buttonImg.emplace_back(trawka.printTerrain(), pair<float, float>(30 * i, 30 * j));
		}
	}
	buttonImg.emplace_back(Gracz->printIcon(), pair<float, float>(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second));
	//buttonImg.emplace_back(Gracz->getShield().printSprite(), pair<float, float>(470, 360));
	//buttonImg.emplace_back(Gracz->getArmour().printSprite(), pair<float, float>(470, 460));

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
	button.emplace_back("Poziom: " + to_string(Gracz->printLvl()) + "\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()), font, green, 22, pair<float, float>(940, 180));
	button.emplace_back(name, font, green, 28, pair<float, float>(780, 40));

	button.emplace_back("PW:\nKP:\nAtak: \nPr", font, green, 22, pair<float, float>(940, 80));
	button.emplace_back(hp + "\n" + ac + "\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n" + to_string(Gracz->printSpeed()), font, green, 22, pair<float, float>(1000, 80));
	button.emplace_back(L"S: \nZr: \nWtr: \nInt: \nRz: \nCh: \n\nWytr: \nRef: \nWola:", font, green, 22, pair<float, float>(1120, 50));
	button.emplace_back(s + "\n" + d + "\n" + c + "\n" + i + "\n" + w + "\n" + ch + "\n\n   " + to_string(Gracz->printSTFor()) + "\n   " + to_string(Gracz->printSTRef()) + "\n   " + to_string(Gracz->printSTWl()), font, green, 22, pair<float, float>(1180, 50));
	button.emplace_back(L"Zmie� bro�", font, green, 22, pair<float, float>(1120, 360), Gracz, Orders::ChangeWeapon);
	button.emplace_back(L"Wyj�cie", font, green, 28, pair<float, float>(1120, 600), GameState::END);


	if (Gracz->isMeleeWeapon()){
		buttonImg.emplace_back(Gracz->getMainWeapon().printSprite(), pair<float, float>(780, 270));
		buttonImg.emplace_back(Gracz->getShield().printSprite(), pair<float, float>(780, 360));
		button.emplace_back(Gracz->getMainWeapon().printWeapon() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, green, 24, pair<float, float>(855, 280));
		button.emplace_back(Gracz->getShield().printShield() + "\n" + shield, font, green, 22, pair<float, float>(855, 360));
	}
	else{
		buttonImg.emplace_back(Gracz->getSecondWeapon().printSprite(), pair<float, float>(780, 270));
		button.emplace_back(distance, font, green, 24, pair<float, float>(855, 280));
	}

	buttonImg.emplace_back(Gracz->getHp().printSprite(), pair<float, float>(940, 40));

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

	buttonImg.emplace_back(leftSprite, pair<float, float>(800, 500), Gracz, Orders2::Left);
	buttonImg.emplace_back(leftTopSprite, pair<float, float>(800, 450), Gracz, Orders2::LeftTop);
	buttonImg.emplace_back(leftDownSprite, pair<float, float>(800, 550), Gracz, Orders2::LeftDown);
	buttonImg.emplace_back(topSprite, pair<float, float>(850, 450), Gracz, Orders2::Top);
	buttonImg.emplace_back(endSprite, pair<float, float>(850, 500), Gracz, Orders2::Left);
	buttonImg.emplace_back(downSprite, pair<float, float>(850, 550), Gracz, Orders2::Down);
	buttonImg.emplace_back(rightSprite, pair<float, float>(900, 500), Gracz, Orders2::Right);
	buttonImg.emplace_back(rightTopSprite, pair<float, float>(900, 450), Gracz, Orders2::RightTop);
	buttonImg.emplace_back(rightDownSprite, pair<float, float>(900, 550), Gracz, Orders2::RightDown);

	printText* hoverPrintText = nullptr;
	printSprite* hoverSprite = nullptr;
	while (state == GameState::GAME)
	{
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
					if (hoverPrintText->getOrder() == Orders::ChangeWeapon){
						Gracz->changeWeapon();
						gamePlay(Gracz);
					}
				}
				if (hoverSprite){
					if ((hoverSprite->getOrder() == Orders2::Left))	{
						pair<int, int>help;
						help = Gracz->getPosition();
						Gracz->setPosition(help.first - 1, help.second);
						gamePlay(Gracz);
					}
					if ((hoverSprite->getOrder() == Orders2::Right))	{
						pair<int, int>help;
						help = Gracz->getPosition();
						Gracz->setPosition(help.first + 1, help.second);
						gamePlay(Gracz);
					}
					if ((hoverSprite->getOrder() == Orders2::LeftDown))	{
						pair<int, int>help;
						help = Gracz->getPosition();
						Gracz->setPosition(help.first - 1, help.second + 1);
						gamePlay(Gracz);
					}
					if ((hoverSprite->getOrder() == Orders2::RightDown))	{
						pair<int, int>help;
						help = Gracz->getPosition();
						Gracz->setPosition(help.first + 1, help.second + 1);
						gamePlay(Gracz);
					}
					if ((hoverSprite->getOrder() == Orders2::LeftTop))	{
						pair<int, int>help;
						help = Gracz->getPosition();
						Gracz->setPosition(help.first - 1, help.second - 1);
						gamePlay(Gracz);
					}
					if ((hoverSprite->getOrder() == Orders2::RightTop))	{
						pair<int, int>help;
						help = Gracz->getPosition();
						Gracz->setPosition(help.first + 1, help.second - 1);
						gamePlay(Gracz);
					}
					if ((hoverSprite->getOrder() == Orders2::Top))	{
						pair<int, int>help;
						help = Gracz->getPosition();
						Gracz->setPosition(help.first, help.second - 1);
						gamePlay(Gracz);
					}
					if ((hoverSprite->getOrder() == Orders2::Down))	{
						pair<int, int>help;
						help = Gracz->getPosition();
						Gracz->setPosition(help.first, help.second + 1);
						gamePlay(Gracz);
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
			window.display();
		}
	}
}
// wzorzec projektowy fabryka