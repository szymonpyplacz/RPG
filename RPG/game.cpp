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
			Gracz->setMainWeapon(WeaponCollection::Fist); //trolololo i tak nie mo¿e
			Gracz->setDistanceWeapon(WeaponCollection::Slingshot);
			Gracz->setArmour(WeaponCollection::LeatherArmor);//trololo i tak nie mo¿e
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
	sf::String distance = Gracz->getSecondWeapon().printWeapon() + " poc. " + to_string(Gracz->getSecondWeapon().printMissles()) + L" zasiêg " + to_string(Gracz->getSecondWeapon().printRange()) + "\n1k" + to_string(Gracz->getSecondWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getSecondWeapon().printCr()) + "/" + Gracz->getSecondWeapon().printCrRg();
	if (Gracz->getSecondWeapon().printWeapon() == "Brak broni dystansowej")
		distance = Gracz->getSecondWeapon().printWeapon();
	sf::String shield = "+" + to_string(Gracz->getShield().getAC()) + " KP";
	if (Gracz->getShield().getAC() == 0)
		shield = "";
	sf::String armour = "+" + to_string(Gracz->getArmour().getAC()) + " KP";
	if (Gracz->getArmour().getAC() == 0)
		armour = "";

	Gracz->setPosition(5, 3, mapa);

	vector<printText> button;
	button.emplace_back(name + "\n\n" + raseName + "\n" + className + "\n\nPoziom: " + to_string(Gracz->printLvl()) + "\n\nPD: " + to_string(Gracz->printExp()) + "/" + to_string(Gracz->printExpToLv()), font, gold, 28, pair<float, float>(260, 50));
	button.emplace_back(hp + "\n\n" + L"Premia do ataku: \n\nPrêdkoœæ \n\nWytrwa³oœæ: \n\nRefleks: \n\nWola: ", font, gold, 22, pair<float, float>(490, 50));
	button.emplace_back(ac + "\n\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n\n" + to_string(Gracz->printSpeed()) + "\n\n" + to_string(Gracz->printSTFor()) + "\n\n" + to_string(Gracz->printSTRef()) + "\n\n" + to_string(Gracz->printSTWl()), font, gold, 22, pair<float, float>(720, 50));
	button.emplace_back(L"Si³a: \n\nZrêcznoœæ: \n\nWytrzyma³oœæ: \n\nIntelekt: \n\nRozs¹dek: \n\nCharyzma: ", font, gold, 22, pair<float, float>(900, 50));
	button.emplace_back(s + "\n\n" + d + "\n\n" + c + "\n\n" + i + "\n\n" + w + "\n\n" + ch, font, gold, 22, pair<float, float>(1130, 50));
	button.emplace_back(Gracz->getMainWeapon().printWeapon() + "\n1k" + to_string(Gracz->getMainWeapon().printWeaponDmg()) + ", kryt. x" + to_string(Gracz->getMainWeapon().printCr()) + "/" + Gracz->getMainWeapon().printCrRg(), font, gold, 24, pair<float, float>(125, 370));
	button.emplace_back(distance, font, gold, 24, pair<float, float>(125, 470));
	button.emplace_back(Gracz->getShield().printShield() + "\n" + shield, font, gold, 22, pair<float, float>(550, 370));
	button.emplace_back(Gracz->getArmour().printArmour() + "\n" + armour, font, gold, 22, pair<float, float>(550, 470));
	button.emplace_back(L"Powrót", font, gold, 28, pair<float, float>(200, 600), GameState::MENU2);
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
	vector<printSprite> buttonImg;
	Gracz->printAvatar().setScale(0.65, 0.65);
	buttonImg.emplace_back(Gracz->printAvatar(), pair<float, float>(770, 70));

	
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

	Text printHpLine(hp + "\n" + ac + "\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n" + to_string(Gracz->printSpeed()), font, 22);
	printHpLine.setColor(green);
	printHpLine.setPosition(1000, 80);

	Sprite hpBar(Gracz->getHp().printSprite());
	hpBar.setPosition(940, 40);
		//buttonImg.emplace_back(Gracz->getHp().printSprite(), pair<float, float>(940, 40));

	button.emplace_back(L"S: \nZr: \nWtr: \nInt: \nRz: \nCh: \n\nWytr: \nRef: \nWola:", font, green, 22, pair<float, float>(1120, 50));
	button.emplace_back(s + "\n" + d + "\n" + c + "\n" + i + "\n" + w + "\n" + ch + "\n\n   " + to_string(Gracz->printSTFor()) + "\n   " + to_string(Gracz->printSTRef()) + "\n   " + to_string(Gracz->printSTWl()), font, green, 22, pair<float, float>(1180, 50));
	button.emplace_back(L"Zmieñ broñ", font, green, 22, pair<float, float>(1120, 360), Gracz, Orders::ChangeWeapon);
	button.emplace_back(L"Wyjœcie", font, green, 28, pair<float, float>(1120, 600), GameState::END);

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
	buttonImg.emplace_back(endSprite, pair<float, float>(850, 500), Gracz, Orders2::EndTurn);
	buttonImg.emplace_back(downSprite, pair<float, float>(850, 550), Gracz, Orders2::Down);
	buttonImg.emplace_back(rightSprite, pair<float, float>(900, 500), Gracz, Orders2::Right);
	buttonImg.emplace_back(rightTopSprite, pair<float, float>(900, 450), Gracz, Orders2::RightTop);
	buttonImg.emplace_back(rightDownSprite, pair<float, float>(900, 550), Gracz, Orders2::RightDown);
	
	Text ruch(L"Pozosta³o " + to_string(Gracz->printLeftMove()), font, 22);
	ruch.setColor(green);
	ruch.setPosition(1000, 500);

	Grass trawka;
	Hill gory;
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 24; j++){
			if (i > 4 && i < 20 && j > 2 && j< 18){
				buttonImg.emplace_back(trawka.printTerrain(), pair<float, float>(30 * i, 30 * j));
			}
			else {
				buttonImg.emplace_back(gory.printTerrain(), pair<float, float>(30 * i, 30 * j));
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
			Gracz->getHp().getDmg(1);
		//zestaw rzeczy do wykonania przed tur¹ //
			for (int i = 0; i < 24; i++){
				for (int j = 0; j < 24; j++){
					if (i > 4 && i < 20 && j > 2 && j< 18){
						buttonImg.emplace_back(trawka.printTerrain(), pair<float, float>(30 * i, 30 * j));
					}
					else
						buttonImg.emplace_back(gory.printTerrain(), pair<float, float>(30 * i, 30 * j));
				}
			}

		Gracz->setCrossedMove();
		Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
		Gracz->setLeftMove();
		ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));

		hpBar.setTexture(Gracz->getHp().printTexture());
		hp = (to_string(Gracz->getHp().printHP()) + "/" + to_string(Gracz->getHp().printMaxHP()));
		printHpLine.setString(hp + "\n" + ac + "\n" + to_string(Gracz->printBasicAttack()) + "/" + to_string(Gracz->printDistanceAttack()) + "\n" + to_string(Gracz->printSpeed()));

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
				// TERAZ PAMIÊTAJ!!!!!!!!!! TRZEBA JESZCZE SPRAWDZI CZY JAKI CIUL NIE WLEZIE NA ZAJÊTE MIEJSCE !!!!!!!!!!!!!
				if (hoverSprite){
					if ((hoverSprite->getOrder() == Orders2::Left) && Gracz->printLeftMove() > 0 && Gracz->getPosition().first > 0 && mapa.isEmpty(make_pair(Gracz->getPosition().first-1, Gracz->getPosition().second)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->setPosition(Gracz->getPosition().first - 1, Gracz->getPosition().second, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));
					}
					else if ((hoverSprite->getOrder() == Orders2::Right) && Gracz->printLeftMove() > 0 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first+1, Gracz->getPosition().second)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->setPosition(Gracz->getPosition().first + 1, Gracz->getPosition().second, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));
					}
					else if ((hoverSprite->getOrder() == Orders2::LeftDown) && ((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().first > 0 && Gracz->getPosition().second<23 && mapa.isEmpty(make_pair(Gracz->getPosition().first-1, Gracz->getPosition().second+1)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->isCrossedMove();
						Gracz->setPosition(Gracz->getPosition().first - 1, Gracz->getPosition().second + 1, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));
					}
					else if ((hoverSprite->getOrder() == Orders2::RightDown) && ((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().second<23 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first + 1, Gracz->getPosition().second + 1)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->isCrossedMove();
						Gracz->setPosition(Gracz->getPosition().first + 1, Gracz->getPosition().second + 1, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));
					}
					else if ((hoverSprite->getOrder() == Orders2::LeftTop) && ((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().first > 0 && Gracz->getPosition().second>0 && mapa.isEmpty(make_pair(Gracz->getPosition().first - 1, Gracz->getPosition().second - 1)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->isCrossedMove();
						Gracz->setPosition(Gracz->getPosition().first - 1, Gracz->getPosition().second - 1, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));
					}
					else if ((hoverSprite->getOrder() == Orders2::RightTop) && ((Gracz->printLeftMove() > 1 && Gracz->wasCrossedMove() == false) || (Gracz->printLeftMove() > 0 && Gracz->wasCrossedMove())) && Gracz->getPosition().second>0 && Gracz->getPosition().first < 23 && mapa.isEmpty(make_pair(Gracz->getPosition().first+1, Gracz->getPosition().second-1)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->isCrossedMove();
						Gracz->setPosition(Gracz->getPosition().first + 1, Gracz->getPosition().second - 1, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));
					}
					else if ((hoverSprite->getOrder() == Orders2::Top) && Gracz->printLeftMove() > 0 && Gracz->getPosition().second>0 && mapa.isEmpty(make_pair(Gracz->getPosition().first, Gracz->getPosition().second - 1)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->setPosition(Gracz->getPosition().first, Gracz->getPosition().second - 1, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));
					}
					else if ((hoverSprite->getOrder() == Orders2::Down) && Gracz->printLeftMove() > 0 && Gracz->getPosition().second<23 && mapa.isEmpty(make_pair(Gracz->getPosition().first, Gracz->getPosition().second + 1)))	{
						mapa.freePosition(Gracz->getPosition());
						Gracz->setPosition(Gracz->getPosition().first, Gracz->getPosition().second + 1, mapa);
						Gracz->printIcon().setPosition(30 * Gracz->getPosition().first, 30 * Gracz->getPosition().second);
						ruch.setString(L"Pozosta³o " + to_string(Gracz->printLeftMove()));
					}

					else if ((hoverSprite->getOrder() == Orders2::EndTurn))	{
						endTurn = true;
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
//
			window.draw(ruch);
			window.display();
		}
	}
}
// wzorzec projektowy fabryka