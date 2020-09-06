#ifndef map_h
#define map_h

#include "Array2D.h"
#include "Tile.h"

class Map{
	
	private:
		Array2D<Tile> tiles;
	
	public:
		Map(size_t lin,size_t col);
		
		size_t getLines() const;
		size_t getColumns() const;
		
		Tile operator()(size_t x,size_t y);
		const Tile operator()(size_t x,size_t y) const;
};

#endif // map_h