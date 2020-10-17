#ifndef ecology_h
#define ecology_h

#include "Map.h"
#include "Living.h"
#include "LivingGroup.h"

class Ecology{
	private:
		Map map;
		std::vector<Living> livingList;
		std::vector<LivingGroup> livingGroupList;
	
	public:
		Ecology(Map pMap);
		Ecology(size_t lin,size_t col);
		Ecology();
		
		const std::vector<Living>& getBestiary() const;
		const std::vector<LivingGroup>& getLivingAt(size_t x,size_t y) const;
};

#endif // ecology_h
