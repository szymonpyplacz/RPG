#include "printSprite.h"
#include "game.h"
#include <SFML\Graphics.hpp>
#pragma once

printSprite::printSprite(Texture texture, pair<float, float> cords){
	button_sprite.setPosition(cords.first, cords.second);
	textured = true;
}

printSprite::printSprite(Sprite photo, pair<float, float> cords) : button_sprite(photo) {
	button_sprite.setPosition(cords.first, cords.second);
	textured = false;
}

printSprite::printSprite(Sprite photo, pair<float, float> cords, Player* gracz, Orders2 metoda) : button_sprite(photo), method(metoda) {
	button_sprite.setPosition(cords.first, cords.second);
	textured = false;

}

Orders2 printSprite::getOrder(){
	return method;
}

sf::Sprite& printSprite::GetSprite()	{
	if (textured)
		button_sprite.setTexture(this->texture);
	return button_sprite;
}
