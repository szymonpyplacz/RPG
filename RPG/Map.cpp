#pragma once
#include "Map.h"
#include <vector>


Map::Map(){
	Grass trawa;
	for (int i = 0; i < 576; i++){
	wektor.emplace_back(trawa);
	}
}

void Map::print(){
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 24; j++){

		}
	}
}