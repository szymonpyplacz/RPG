#include "game.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Windows.h>
#include <string>
#include "player.h"
#include "WeaponCollection.h"

//24 punkty do budowy postaci

Game::Game(void)
{
		state = END;
	if ((!background.loadFromFile("bg3.jpg")) || (!background2.loadFromFile("bg2.jpg")) || (!background3.loadFromFile("bg.gif")))
		return;



	state = MENU;

	if (!font.loadFromFile("font_one.ttf"))	{
		MessageBox(NULL, "Font not found", "ERROR", NULL);
		return;
	}
	state = MENU;
};


void Game::runGame()
{
	while (state != END)
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


	RenderWindow oknoAplikacji(sf::VideoMode(1280, 720, 32), "Silance of the night");
	oknoAplikacji.setKeyRepeatEnabled(false);
	background2.setSmooth(true);
	bg.setTexture(background2);

	
	Text title(L"Witaj dzielny œmia³ku, \nOd Twojego zadania\n  Zale¿¹ losy\n  nas wszystkich", font, 48);
	title.setPosition((1280 / 2 - title.getGlobalBounds().width / 2) - 70, 20);
	title.setColor(Color::Black);
	Text newGame(L"Nowa Gra", font, 36);
	newGame.setPosition(100 + (1280 / 2 - title.getGlobalBounds().width / 2), 300);
	newGame.setColor(Color::Black);
	Text cont(L"Graj dalej", font, 36);
	cont.setPosition(100 + (1280 / 2 - title.getGlobalBounds().width / 2), 350);
	cont.setColor(Color::Black);
	Text end(L"WyjdŸ z gry", font, 36);
	end.setPosition(350 + (1280 / 2 - title.getGlobalBounds().width / 2), 500);
	end.setColor(Color::Black);


	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(oknoAplikacji));
		Event event;
		while (oknoAplikacji.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				state = END;
			if (end.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = END;

			if (newGame.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = MENU2;

			if (newGame.getGlobalBounds().contains(mouse))
				newGame.setStyle(Text::Underlined);
			else
				newGame.setStyle(Text::Regular);

			if (cont.getGlobalBounds().contains(mouse))
				cont.setStyle(Text::Underlined);
			else
				cont.setStyle(Text::Regular);

			if (end.getGlobalBounds().contains(mouse))
				end.setStyle(Text::Underlined);
			else
				end.setStyle(Text::Regular);

		}
		oknoAplikacji.clear();
		oknoAplikacji.draw(bg);
		oknoAplikacji.draw(title);
		oknoAplikacji.draw(newGame);
		oknoAplikacji.draw(cont);
		oknoAplikacji.draw(end);
		oknoAplikacji.display();
	}
}

void Game::newPlayer(){

	RenderWindow oknoAplikacji(sf::VideoMode(1280, 720, 32), "Silance of the night");
	oknoAplikacji.setKeyRepeatEnabled(false);
	background.setSmooth(true);
	bg.setTexture(background);

	Text title(L"Wybierz któregoœ z bohaterów", font, 48);
	title.setPosition(1280 / 3 - title.getGlobalBounds().width / 2, 20);
	title.setColor(Color::Black);

	Text Fighter(L"Khelgar, krasnolud wojownik", font, 32);
	Fighter.setPosition(1280 / 2 - Fighter.getGlobalBounds().width, 200);
	Fighter.setColor(Color::Black);

	Text Wizard(L"Aethan, mag cz³owiek", font, 32);
	Wizard.setPosition(1280 / 2 - Fighter.getGlobalBounds().width, 260);
	Wizard.setColor(Color::Black);

	Text Hunter(L"Thárwen, elfka tropiciel", font, 32);
	Hunter.setPosition(1280 / 2 - Fighter.getGlobalBounds().width, 320);
	Hunter.setColor(Color::Black);

	Text Create(L"Stwórz swoj¹ postaæ", font, 32);
	Create.setPosition(1280 / 2 - Fighter.getGlobalBounds().width, 400);
	Create.setColor(Color::Black);

	Text back(L"Powrót", font, 32);
	back.setPosition(1280 / 3 - back.getGlobalBounds().width, 600);
	back.setColor(Color::Black);

	while (state == MENU2)
	{
		Vector2f mouse(Mouse::getPosition(oknoAplikacji));
		Event event;
		while (oknoAplikacji.pollEvent(event))
		{
			if (back.getGlobalBounds().contains(mouse))
				back.setStyle(Text::Underlined);
			else
				back.setStyle(Text::Regular);

			if (Fighter.getGlobalBounds().contains(mouse))
				Fighter.setStyle(Text::Underlined);
			else
				Fighter.setStyle(Text::Regular);

			if (Wizard.getGlobalBounds().contains(mouse))
				Wizard.setStyle(Text::Underlined);
			else
				Wizard.setStyle(Text::Regular);

			if (Hunter.getGlobalBounds().contains(mouse))
				Hunter.setStyle(Text::Underlined);
			else
				Hunter.setStyle(Text::Regular);

			if (Fighter.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = MENU2_a;

			if (Wizard.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = MENU2_b;

			if (Hunter.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = MENU2_c;
		
			if (back.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = MENU;
		}

		oknoAplikacji.clear();
		oknoAplikacji.draw(bg);
		oknoAplikacji.draw(title);
		oknoAplikacji.draw(Fighter);
		oknoAplikacji.draw(Wizard);
		oknoAplikacji.draw(Hunter);
		//	oknoAplikacji.draw(Create);
		oknoAplikacji.draw(back);
		oknoAplikacji.display();
	}
}

///// the first played character - dwarf /////

void::Game::khelgar() {
	RenderWindow oknoAplikacji(sf::VideoMode(1280, 720, 32), "Silance of the night");
	oknoAplikacji.setKeyRepeatEnabled(false);
	background3.setSmooth(true);
	bg.setTexture(background3);

	Texture wood;
	wood.loadFromFile("belka.gif");
	wood.setSmooth(true);
	Sprite woodPct;
	woodPct.setTexture(wood);
	woodPct.setPosition(430, 35);
	Sprite woodPct2;
	woodPct2.setTexture(wood);
	woodPct2.setPosition(820, 35);
	
	Player* Khelgar = new Player(Player::fighter, Player::dwarf, Ability(15), Ability(12), Ability(14), Ability(10), Ability(10), Ability(10), Level(0), Armor(), true, "Khelgar");

	Sprite dwarfPicture;
	dwarfPicture = Khelgar->printAvatar();
	dwarfPicture.setPosition(45, 40);

	Khelgar->mainWeapon = WeaponCollection::TwoHandedAxe;
	Sprite weap;
	weap = Khelgar->mainWeapon.printSprite();
	weap.setPosition(50, 360);


	Color bl(66, 137, 255);
	Color gr(109, 213, 2);
	Color gold(252, 255, 166);
	Color r(219, 22, 5);
	
	string s = Khelgar->printStr();
	string d = Khelgar->printDex();
	string c = Khelgar->printCon();
	string i = Khelgar->printInt();
	string w = Khelgar->printWis();
	string ch = Khelgar->printCha();
	string className = Khelgar->printClassName();
	string raseName = Khelgar->printRaseName();
	//Sing::GetInstance().GetTwoHandedAxe;

	string name = Khelgar->printName();
	string hp = ("PW: " + to_string(Khelgar->printHpNow()) + "/" + to_string(Khelgar->printHpMax()));
	string ac = ("KP: " + to_string(Khelgar->printAC()));


	Text khelgar(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Khelgar->printLvl()) + "\n\nPD: " + to_string(Khelgar->printExp()) + "/" + to_string(Khelgar->printExpToLv()), font, 28);
	khelgar.setPosition(260, 50);
	khelgar.setColor(gold);
	khelgar.setStyle(2);


	Text basicAtack(hp + "\n\n" + L"Premia do ataku: \n\nPrêdkoœæ \n\nWytrwa³oœæ: \n\nRefleks: \n\nWola: ", font, 22);
	basicAtack.setPosition(490, 50);
	basicAtack.setColor(gold);
	basicAtack.setStyle(0);
	
	Text basicAtackVal(ac + "\n\n" + to_string(Khelgar->printBasicAttack()) + "/" + to_string(Khelgar->printDistanceAttack()) + "\n\n" + to_string(Khelgar->printSpeed()) + "\n\n" + to_string(Khelgar->printSTFor()) + "\n\n" + to_string(Khelgar->printSTRef()) + "\n\n" + to_string(Khelgar->printSTWl()), font, 22);
	basicAtackVal.setPosition(720, 50);
	basicAtackVal.setColor(gold);
	basicAtackVal.setStyle(0);

	Text artName(L"Si³a: \n\nZrêcznoœæ: \n\nWytrzyma³oœæ: \n\nIntelekt: \n\nRozs¹dek: \n\nCharyzma: ", font, 22);
	artName.setPosition(900, 50);
	artName.setColor(gold);
	artName.setStyle(0);

	Text artVal( s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, 22);
	artVal.setPosition(1130, 50);
	artVal.setColor(gold);
	artVal.setStyle(0);

	Text weapText(Khelgar->mainWeapon.printWeapon() + "\n1k" + to_string(Khelgar->mainWeapon.printWeaponDmg()) + ", kryt. x" + to_string(Khelgar->mainWeapon.printCr()) + "/" + Khelgar->mainWeapon.printCrRg(), font, 24);
	weapText.setPosition(125, 370);
	weapText.setColor(gold);
	weapText.setStyle(2);


	Text back(L"Powrót", font, 28);
	back.setPosition(1280 / 3 - back.getGlobalBounds().width, 600);
	back.setColor(gold);

	while (state == MENU2_a)
	{

		Vector2f mouse(Mouse::getPosition(oknoAplikacji));
		Event event;
		while (oknoAplikacji.pollEvent(event)){
		
		if (back.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			state = MENU2;
		
		if (back.getGlobalBounds().contains(mouse))
			back.setStyle(Text::Underlined);
		else
			back.setStyle(Text::Regular);

		oknoAplikacji.clear();
		oknoAplikacji.draw(bg);
		oknoAplikacji.draw(khelgar);
		oknoAplikacji.draw(artName);
		oknoAplikacji.draw(artVal);
		oknoAplikacji.draw(basicAtack);
		oknoAplikacji.draw(basicAtackVal);
		oknoAplikacji.draw(dwarfPicture);
		oknoAplikacji.draw(weapText);
		oknoAplikacji.draw(woodPct);
		oknoAplikacji.draw(woodPct2);
		oknoAplikacji.draw(weap);
		oknoAplikacji.draw(back);
		oknoAplikacji.display();

		}
	}
}

///// the second played character - elf /////

void::Game::tharwen() {
	RenderWindow oknoAplikacji(sf::VideoMode(1280, 720, 32), "Silance of the night");
	oknoAplikacji.setKeyRepeatEnabled(false);
	background3.setSmooth(true);
	bg.setTexture(background3);
	Texture wood;
	wood.loadFromFile("belka.gif");
	wood.setSmooth(true);
	Sprite woodPct;
	woodPct.setTexture(wood);
	woodPct.setPosition(430, 35);
	Sprite woodPct2;
	woodPct2.setTexture(wood);
	woodPct2.setPosition(820, 35);


	Player* Tharwen = new Player(Player::hunter, Player::elf, Ability(15), Ability(14), Ability(12), Ability(10), Ability(10), Ability(10), Level(0), Armor(), false, "Tharwen");

	Sprite elfPicture;
	elfPicture = Tharwen->printAvatar();
	elfPicture.setPosition(45, 40);

	Tharwen->mainWeapon = WeaponCollection::Longsword;
	Sprite weap;
	weap = Tharwen->mainWeapon.printSprite();
	weap.setPosition(50, 360);

	Color bl(66, 137, 255);
	Color gr(109, 213, 2);
	Color gold(252, 255, 166);
	Color r(219, 22, 5);

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


	Text tharwen(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Tharwen->printLvl()) + "\n\nPD: " + to_string(Tharwen->printExp()) + "/" + to_string(Tharwen->printExpToLv()), font, 28);
	tharwen.setPosition(260, 50);
	tharwen.setColor(gold);
	tharwen.setStyle(2);


	Text basicAtack(hp + "\n\n" + L"Premia do ataku: \n\nPrêdkoœæ \n\nWytrwa³oœæ: \n\nRefleks: \n\nWola: ", font, 22);
	basicAtack.setPosition(490, 50);
	basicAtack.setColor(gold);
	basicAtack.setStyle(0);

	Text basicAtackVal(ac + "\n\n" + to_string(Tharwen->printBasicAttack()) + "/" + to_string(Tharwen->printDistanceAttack()) + "\n\n" + to_string(Tharwen->printSpeed()) + "\n\n" + to_string(Tharwen->printSTFor()) + "\n\n" + to_string(Tharwen->printSTRef()) + "\n\n" + to_string(Tharwen->printSTWl()), font, 22);
	basicAtackVal.setPosition(720, 50);
	basicAtackVal.setColor(gold);
	basicAtackVal.setStyle(0);

	Text artName(L"Si³a: \n\nZrêcznoœæ: \n\nWytrzyma³oœæ: \n\nIntelekt: \n\nRozs¹dek: \n\nCharyzma: ", font, 22);
	artName.setPosition(900, 50);
	artName.setColor(gold);
	artName.setStyle(0);

	Text artVal(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, 22);
	artVal.setPosition(1130, 50);
	artVal.setColor(gold);
	artVal.setStyle(0);

	Text weapText(Tharwen->mainWeapon.printWeapon() + "\n1k" + to_string(Tharwen->mainWeapon.printWeaponDmg()) + ", kryt. x" + to_string(Tharwen->mainWeapon.printCr()) + "/" + Tharwen->mainWeapon.printCrRg(), font, 24);
	weapText.setPosition(125, 370);
	weapText.setColor(gold);
	weapText.setStyle(2);

	Text back(L"Powrót", font, 28);
	back.setPosition(1280 / 3 - back.getGlobalBounds().width, 600);
	back.setColor(gold);

	while (state == MENU2_c)
	{

		Vector2f mouse(Mouse::getPosition(oknoAplikacji));
		Event event;
		while (oknoAplikacji.pollEvent(event)){

			if (back.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = MENU2;

			if (back.getGlobalBounds().contains(mouse))
				back.setStyle(Text::Underlined);
			else
				back.setStyle(Text::Regular);

			oknoAplikacji.clear();
			oknoAplikacji.draw(bg);
			oknoAplikacji.draw(tharwen);
			oknoAplikacji.draw(artName);
			oknoAplikacji.draw(artVal);
			oknoAplikacji.draw(basicAtack);
			oknoAplikacji.draw(basicAtackVal);
			oknoAplikacji.draw(elfPicture);
			oknoAplikacji.draw(weap);
			oknoAplikacji.draw(weapText);
			oknoAplikacji.draw(woodPct);
			oknoAplikacji.draw(woodPct2);
			oknoAplikacji.draw(back);
			oknoAplikacji.display();
		}
	}
}

// the last created person
//

void::Game::rodger() {
	RenderWindow oknoAplikacji(sf::VideoMode(1280, 720, 32), "Silance of the night");
	oknoAplikacji.setKeyRepeatEnabled(false);
	background3.setSmooth(true);
	bg.setTexture(background3);
	Texture wood;
	wood.loadFromFile("belka.gif");
	wood.setSmooth(true);
	Sprite woodPct;
	woodPct.setTexture(wood);
	woodPct.setPosition(430, 35);
	Sprite woodPct2;
	woodPct2.setTexture(wood);
	woodPct2.setPosition(820, 35);




Player* Rodger = new Player(Player::wizard, Player::human, Ability(8), Ability(12), Ability(10), Ability(16), Ability(14), Ability(10), Level(0), Armor(), true, "Rodger");

Sprite manPicture;
manPicture = Rodger->printAvatar();
manPicture.setPosition(45, 40);

Sprite weap;
weap = Rodger->mainWeapon.printSprite();
weap.setPosition(50, 360);


Color bl(66, 137, 255);
Color gr(109, 213, 2);
Color gold(252, 255, 166);
Color r(219, 22, 5);

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


Text tharwen(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Rodger->printLvl()) + "\n\nPD: " + to_string(Rodger->printExp()) + "/" + to_string(Rodger->printExpToLv()), font, 28);
tharwen.setPosition(260, 50);
tharwen.setColor(gold);
tharwen.setStyle(2);

Text basicAtack(hp + "\n\n" + L"Premia do ataku: \n\nPrêdkoœæ \n\nWytrwa³oœæ: \n\nRefleks: \n\nWola: ", font, 22);
basicAtack.setPosition(490, 50);
basicAtack.setColor(gold);
basicAtack.setStyle(0);

Text basicAtackVal(ac + "\n\n" + to_string(Rodger->printBasicAttack()) + "/" + to_string(Rodger->printDistanceAttack()) + "\n\n" + to_string(Rodger->printSpeed()) + "\n\n" + to_string(Rodger->printSTFor()) + "\n\n" + to_string(Rodger->printSTRef()) + "\n\n" + to_string(Rodger->printSTWl()), font, 22);
basicAtackVal.setPosition(720, 50);
basicAtackVal.setColor(gold);
basicAtackVal.setStyle(0);

Text artName(L"Si³a: \n\nZrêcznoœæ: \n\nWytrzyma³oœæ: \n\nIntelekt: \n\nRozs¹dek: \n\nCharyzma: ", font, 22);
artName.setPosition(900, 50);
artName.setColor(gold);
artName.setStyle(0);

Text artVal(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, 22);
artVal.setPosition(1130, 50);
artVal.setColor(gold);
artVal.setStyle(0);

Text weapText(Rodger->mainWeapon.printWeapon() + "\n1k" + to_string(Rodger->mainWeapon.printWeaponDmg()) + ", kryt. x" + to_string(Rodger->mainWeapon.printCr()) + "/" + Rodger->mainWeapon.printCrRg(), font, 24);
weapText.setPosition(125, 370);
weapText.setColor(gold);
weapText.setStyle(2);

Text back(L"Powrót", font, 28);
back.setPosition(1280 / 3 - back.getGlobalBounds().width, 600);
back.setColor(gold);

while (state == MENU2_b)
{

	Vector2f mouse(Mouse::getPosition(oknoAplikacji));
	Event event;
	while (oknoAplikacji.pollEvent(event)){

		if (back.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			state = MENU2;

		if (back.getGlobalBounds().contains(mouse))
			back.setStyle(Text::Underlined);
		else
			back.setStyle(Text::Regular);

		oknoAplikacji.clear();
		oknoAplikacji.draw(bg);
		oknoAplikacji.draw(tharwen);
		oknoAplikacji.draw(artName);
		oknoAplikacji.draw(artVal);
		oknoAplikacji.draw(basicAtack);
		oknoAplikacji.draw(basicAtackVal);
		oknoAplikacji.draw(manPicture);
		oknoAplikacji.draw(weap);
		oknoAplikacji.draw(weapText);
		oknoAplikacji.draw(woodPct);
		oknoAplikacji.draw(woodPct2);
		oknoAplikacji.draw(back);
		oknoAplikacji.display();
	}
}
}


// wzorzec projektowy fabryka