#include "Tile.h"

#include "general.h"

Tile::Tile(int temp,int hum,int nut,int elev) : temperature(temp),humidity(hum),nutrients(nut),elevation(elev){}

Tile::Tile() : Tile(randomInt(-100,100),randomInt(100),randomInt(100),randomInt(-100,100)){}

int Tile::getTemp() const{
	return temperature;
}

int Tile::getHum() const{
	return humidity;
}

int Tile::getNut() const{
	return nutrients;
}

int Tile::getElev() const{
	return elevation;
}
