#ifndef gas_planet_h
#define gas_planet_h

#include "World.h"

class GasPlanet : public World{
	public:
		GasPlanet(size_t r,AstralObject* o,size_t d);
		
		bool isGasPlanet() const;
};

#endif // gas_planet_h
