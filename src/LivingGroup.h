#ifndef living_group_h
#define living_group_h

#include <stddef.h> // size_t

#include "Living.h"
#include "Tile.h"

enum class Position{
	NOWHERE = 0,
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class LivingGroup{
	private:
		const Living& living;
		int population;
		size_t x;
		size_t y;
	
	public:
		LivingGroup(const Living& pLiving,int pPopulation,size_t pX,size_t pY);
		
		bool canMoveTo(const Tile& tile);
		void moveTo(Position pos);
		
		int getPopulation() const;
		size_t getX() const;
		size_t getY() const;
};

#endif // living_group_h
