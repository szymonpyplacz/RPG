#include "game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Windows.h>
#include <string>
#include "player.h"
#include "printText.h"
#include "printSprite.h"

//24 punkty do budowy postaci

Game::Game(void) : window(VideoMode(1280, 720, 32), "", Style::None)
{
	window.setPosition(Vector2i(300, 100));
	window.setKeyRepeatEnabled(true);
	state = GameState::END;


	if ((!background.loadFromFile("bg3.jpg")) || (!background2.loadFromFile("bg2.jpg")) || (!background3.loadFromFile("bg.gif")))
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
		muzyka.play();
		muzyka.setVolume(30);
		
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::MENU2:
			newPlayer();
			break;
		case GameState::MENU2_a:
			khelgar();
			break;
		case GameState::MENU2_b:
			rodger();
			break;
		case GameState::MENU2_c:
			tharwen();
			break;
		}
	}
}


void Game::menu()
{
	bg.setTexture(background2);
	vector<printText> button;
	button.emplace_back(L"Witaj dzielny œmia³ku, \nOd Twojego zadania\n  Zale¿¹ losy\n  nas wszystkich", font, Color::Black, 48, pair<float, float>(300, 20));
	button.emplace_back(L"Nowa Gra", font, Color::Black, 36, pair<float, float>(650, 300), GameState::MENU2);
	button.emplace_back(L"Graj dalej", font, Color::Black, 36, pair<float, float>(650, 350));
	button.emplace_back(L"WyjdŸ z gry", font, Color::Black, 36, pair<float, float>(700, 500), GameState::END);

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
	button.emplace_back(L"Wybierz któregoœ z bohaterów", font, Color::Black, 48, pair<float, float>(120, 20));
	button.emplace_back(L"Khelgar, krasnolud wojownik", font, Color::Black, 32, pair<float, float>(120, 200), GameState::MENU2_a);
	button.emplace_back(L"Rodger, mag cz³owiek", font, Color::Black, 32, pair<float, float>(120, 260), GameState::MENU2_b);
	button.emplace_back(L"Thárwen, elfka tropiciel", font, Color::Black, 32, pair<float, float>(120, 320), GameState::MENU2_c);
	button.emplace_back(L"Powrót", font, Color::Black, 32, pair<float, float>(120, 600), GameState::MENU);

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

///// the first played character - dwarf /////

void::Game::khelgar() {
	bg.setTexture(background3);
	Texture wood;
	wood.loadFromFile("belka.gif");
	vector<printSprite> buttonImg;
	buttonImg.emplace_back(wood, pair<float, float>(430, 35));
	buttonImg.emplace_back(wood, pair<float, float>(820, 35));
	
	Player* Khelgar = new Player(playerClass::fighter, rase::dwarf, Ability(15), Ability(12), Ability(14), Ability(10), Ability(10), Ability(10), Level(0), Armor(), true, "Khelgar");
	Khelgar->setMainWeapon(WeaponCollection::TwoHandedAxe);

	buttonImg.emplace_back(Khelgar->printAvatar(), pair<float, float>(45, 40));
	buttonImg.emplace_back(Khelgar->getMainWeapon().printSprite(), pair<float, float>(50, 360));
	
	Color gold(252, 255, 166);

	string s = Khelgar->printStr();
	string d = Khelgar->printDex();
	string c = Khelgar->printCon();
	string i = Khelgar->printInt();
	string w = Khelgar->printWis();
	string ch = Khelgar->printCha();
	string className = Khelgar->printClassName();
	string raseName = Khelgar->printRaseName();
	string name = Khelgar->printName();
	string hp = ("PW: " + to_string(Khelgar->printHpNow()) + "/" + to_string(Khelgar->printHpMax()));
	string ac = ("KP: " + to_string(Khelgar->printAC()));
	//Sing::GetInstance().GetTwoHandedAxe;
	
	vector<printText> button;
	button.emplace_back(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Khelgar->printLvl()) + "\n\nPD: " + to_string(Khelgar->printExp()) + "/" + to_string(Khelgar->printExpToLv()), font, gold, 28, pair<float, float>(260, 50));
	button.emplace_back(hp + "\n\n" + L"Premia do ataku: \n\nPrêdkoœæ \n\nWytrwa³oœæ: \n\nRefleks: \n\nWola: ", font, gold, 22, pair<float, float>(490, 50));
	button.emplace_back(ac + "\n\n" + to_string(Khelgar->printBasicAttack()) + "/" + to_string(Khelgar->printDistanceAttack()) + "\n\n" + to_string(Khelgar->printSpeed()) + "\n\n" + to_string(Khelgar->printSTFor()) + "\n\n" + to_string(Khelgar->printSTRef()) + "\n\n" + to_string(Khelgar->printSTWl()), font, gold, 22, pair<float, float>(720, 50));
	button.emplace_back(L"Si³a: \n\nZrêcznoœæ: \n\nWytrzyma³oœæ: \n\nIntelekt: \n\nRozs¹dek: \n\nCharyzma: ", font, gold, 22, pair<float, float>(900, 50));
	button.emplace_back(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, gold, 22, pair<float, float>(1130, 50));
	button.emplace_back(Khelgar->getMainWeapon().printWeapon() + "\n1k" + to_string(Khelgar->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Khelgar->getMainWeapon().printCr()) + "/" + Khelgar->getMainWeapon().printCrRg(), font, gold, 24, pair<float, float>(125, 370));
	button.emplace_back(L"Powrót", font, gold, 28, pair<float, float>(200, 600), GameState::MENU2);
	button.emplace_back(L"Dalej", font, gold, 28, pair<float, float>(800, 600), GameState::MENU2);

	printText* hoverPrintText = nullptr;
	while (state == GameState::MENU2_a)
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

///// the second played character - elf /////

void::Game::tharwen() {
	bg.setTexture(background3);
	Texture wood;
	wood.loadFromFile("belka.gif");
	vector<printSprite> buttonImg;
	buttonImg.emplace_back(wood, pair<float, float>(430, 35));
	buttonImg.emplace_back(wood, pair<float, float>(820, 35));

	Player* Tharwen = new Player(playerClass::hunter, rase::elf, Ability(15), Ability(14), Ability(12), Ability(10), Ability(10), Ability(10), Level(0), Armor(), false, "Tharwen");
	Tharwen->setMainWeapon(WeaponCollection::Longsword);
	Tharwen->setDistanceWeapon(WeaponCollection::Bow);

	buttonImg.emplace_back(Tharwen->printAvatar(), pair<float, float>(45, 40));
	buttonImg.emplace_back(Tharwen->getMainWeapon().printSprite(), pair<float, float>(50, 360));
	buttonImg.emplace_back(Tharwen->getSecondWeapon().printSprite(), pair<float, float>(50, 460));

	Color gold(252, 255, 166);

	string s = Tharwen->printStr();
	string d = Tharwen->printDex();
	string c = Tharwen->printCon();
	string i = Tharwen->printInt();
	string w = Tharwen->printWis();
	string ch = Tharwen->printCha();
	string className = Tharwen->printClassName();
	string raseName = Tharwen->printRaseName();
	string name = Tharwen->printName();
	string hp = ("PW: " + to_string(Tharwen->printHpNow()) + "/" + to_string(Tharwen->printHpMax()));
	string ac = ("KP: " + to_string(Tharwen->printAC()));
	//ona jedna ma dwie bronie
	vector<printText> button;
	button.emplace_back(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Tharwen->printLvl()) + "\n\nPD: " + to_string(Tharwen->printExp()) + "/" + to_string(Tharwen->printExpToLv()), font, gold, 28, pair<float, float>(260, 50));
	button.emplace_back(hp + "\n\n" + L"Premia do ataku: \n\nPrêdkoœæ \n\nWytrwa³oœæ: \n\nRefleks: \n\nWola: ", font, gold, 22, pair<float, float>(490, 50));
	button.emplace_back(ac + "\n\n" + to_string(Tharwen->printBasicAttack()) + "/" + to_string(Tharwen->printDistanceAttack()) + "\n\n" + to_string(Tharwen->printSpeed()) + "\n\n" + to_string(Tharwen->printSTFor()) + "\n\n" + to_string(Tharwen->printSTRef()) + "\n\n" + to_string(Tharwen->printSTWl()), font, gold, 22, pair<float, float>(720, 50));
	button.emplace_back(L"Si³a: \n\nZrêcznoœæ: \n\nWytrzyma³oœæ: \n\nIntelekt: \n\nRozs¹dek: \n\nCharyzma: ", font, gold, 22, pair<float, float>(900, 50));
	button.emplace_back(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, gold, 22, pair<float, float>(1130, 50));
	button.emplace_back(Tharwen->getMainWeapon().printWeapon() + "\n1k" + to_string(Tharwen->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Tharwen->getMainWeapon().printCr()) + "/" + Tharwen->getMainWeapon().printCrRg(), font, gold, 24, pair<float, float>(125, 370));
	button.emplace_back(Tharwen->getSecondWeapon().printWeapon() + "\n1k" + to_string(Tharwen->getSecondWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Tharwen->getSecondWeapon().printCr()) + "/" + Tharwen->getSecondWeapon().printCrRg(), font, gold, 24, pair<float, float>(125, 470));
	button.emplace_back(L"Powrót", font, gold, 28, pair<float, float>(200, 600), GameState::MENU2);
	button.emplace_back(L"Dalej", font, gold, 28, pair<float, float>(800, 600), GameState::MENU2);

	printText* hoverPrintText = nullptr;
	while (state == GameState::MENU2_c)
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

// the last created person

void::Game::rodger() {
	bg.setTexture(background3);
	Texture wood;
	wood.loadFromFile("belka.gif");
	vector<printSprite> buttonImg;
	buttonImg.emplace_back(wood, pair<float, float>(430, 35));
	buttonImg.emplace_back(wood, pair<float, float>(820, 35));

Player* Rodger = new Player(playerClass::wizard, rase::human, Ability(8), Ability(12), Ability(10), Ability(16), Ability(14), Ability(10), Level(0), Armor(), true, "Rodger");

buttonImg.emplace_back(Rodger->printAvatar(), pair<float, float>(45, 40));
buttonImg.emplace_back(Rodger->getMainWeapon().printSprite(), pair<float, float>(50, 360));

Color gold(252, 255, 166);

string s = Rodger->printStr();
string d = Rodger->printDex();
string c = Rodger->printCon();
string i = Rodger->printInt();
string w = Rodger->printWis();
string ch = Rodger->printCha();
string className = Rodger->printClassName();
string raseName = Rodger->printRaseName();
string name = Rodger->printName();
string hp = ("PW: " + to_string(Rodger->printHpNow()) + "/" + to_string(Rodger->printHpMax()));
string ac = ("KP: " + to_string(Rodger->printAC()));

vector<printText> button;
button.emplace_back(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Rodger->printLvl()) + "\n\nPD: " + to_string(Rodger->printExp()) + "/" + to_string(Rodger->printExpToLv()), font, gold, 28, pair<float, float>(260, 50));
button.emplace_back(hp + "\n\n" + L"Premia do ataku: \n\nPrêdkoœæ \n\nWytrwa³oœæ: \n\nRefleks: \n\nWola: ", font, gold, 22, pair<float, float>(490, 50));
button.emplace_back(ac + "\n\n" + to_string(Rodger->printBasicAttack()) + "/" + to_string(Rodger->printDistanceAttack()) + "\n\n" + to_string(Rodger->printSpeed()) + "\n\n" + to_string(Rodger->printSTFor()) + "\n\n" + to_string(Rodger->printSTRef()) + "\n\n" + to_string(Rodger->printSTWl()), font, gold, 22, pair<float, float>(720, 50));
button.emplace_back(L"Si³a: \n\nZrêcznoœæ: \n\nWytrzyma³oœæ: \n\nIntelekt: \n\nRozs¹dek: \n\nCharyzma: ", font, gold, 22, pair<float, float>(900, 50));
button.emplace_back(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, gold, 22, pair<float, float>(1130, 50));
button.emplace_back(Rodger->getMainWeapon().printWeapon() + "\n1k" + to_string(Rodger->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Rodger->getMainWeapon().printCr()) + "/" + Rodger->getMainWeapon().printCrRg(), font, gold, 24, pair<float, float>(125, 370));
button.emplace_back(L"Powrót", font, gold, 28, pair<float, float>(200, 600), GameState::MENU2);
button.emplace_back(L"Dalej", font, gold, 28, pair<float, float>(800, 600), GameState::MENU2);

printText* hoverPrintText = nullptr;
while (state == GameState::MENU2_b)
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
// wzorzec projektowy fabryka