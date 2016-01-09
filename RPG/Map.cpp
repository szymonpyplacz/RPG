#include "Map.h"

Map::Map(){

}

void Map::addPosition(std::pair<int, int> kordy){
	busyPosition.emplace_back(kordy);
};

void Map::freePosition(std::pair<int, int> kordy){
	for (int i = 0; busyPosition.size(); i++){
		if (busyPosition[i].first == kordy.first && busyPosition[i].second == kordy.second){
			busyPosition.erase(busyPosition.begin() + i);
			break;
		}
	}
}

bool Map::isEmpty(std::pair<int, int> kordy){
	for (int i = 0; i <busyPosition.size(); i++){
		if (busyPosition[i].first == kordy.first && busyPosition[i].second == kordy.second){
			return false;
		}
	}
	return true;
}
