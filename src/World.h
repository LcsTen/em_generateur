#ifndef world_h
#define world_h

#include "AstralObject.h"

#include <stddef.h>
#include <string>

class World : public AstralObject{
	private:
		std::string name;
		AstralObject* orbiting;
		size_t distance;
	
	public:
		World(size_t r,AstralObject* o,size_t d);
		virtual ~World() = default;
		
		virtual bool isGasPlanet() const = 0;
		std::string getName() const;
		AstralObject* getOrbiting();
		size_t getDistance() const;
		bool isWorld() const;
};

#endif // world_h
