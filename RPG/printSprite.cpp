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

sf::Sprite& printSprite::GetSprite()	{
	if (textured)
		button_sprite.setTexture(this->texture);
	return button_sprite;
}
