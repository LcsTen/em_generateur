#include "TelluricPlanet.h"

#include "general.h"

TelluricPlanet::TelluricPlanet(size_t r,AstralObject* o,size_t d) : World(r,o,d){
	atmosphereDensity = randomInt(120);
}

size_t TelluricPlanet::getAtmosphereDensity() const{
	return atmosphereDensity;
}

size_t TelluricPlanet::getHottestTemperature() const{
	return hottestTemperature;
}

size_t TelluricPlanet::getColdestTemperature() const{
	return coldestTemperature;
}

bool TelluricPlanet::isGasPlanet() const{
	return false;
}

void TelluricPlanet::setHottestTemperature(size_t v){
	hottestTemperature = v;
}

void TelluricPlanet::setColdestTemperature(size_t v){
	coldestTemperature = v;
}
