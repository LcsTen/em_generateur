#ifndef telluric_planet_h
#define telluric_planet_h

#include "World.h"

class TelluricPlanet : public World{
	private:
		size_t atmosphereDensity;
		size_t hottestTemperature;
		size_t coldestTemperature;
	
	public:
		TelluricPlanet(size_t r,AstralObject* o,size_t d);
		
		size_t getAtmosphereDensity() const;
		size_t getHottestTemperature() const;
		size_t getColdestTemperature() const;
		bool isGasPlanet() const;
		
		void setHottestTemperature(size_t v);
		void setColdestTemperature(size_t v);
};

#endif // telluric_planet_h
