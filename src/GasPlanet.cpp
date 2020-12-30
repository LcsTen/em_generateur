#include "GasPlanet.h"

GasPlanet::GasPlanet(size_t r,AstralObject* o,size_t d) : World(r,o,d){}

bool GasPlanet::isGasPlanet() const{
	return true;
}
