#include "Map.h"

Map::Map(size_t lin,size_t col) : tiles(lin,col){
	for(size_t y = 0;y < lin;y++){
		for(size_t x = 0;x < col;x++){
			Tile tile;
			tiles(x,y) = tile;
		}
	}
}

size_t Map::getLines() const{
	return tiles.lines();
}

size_t Map::getColumns() const{
	return tiles.columns();
}

Tile Map::operator()(size_t x,size_t y){
	return tiles(x,y);
}

const Tile Map::operator()(size_t x,size_t y) const{
	return tiles(x,y);
}
