#include "Star.h"

Star::Star(size_t t,size_t r,char c[2]) : AstralObject(r), temperature(t){
	starClass[0] = c[0];
	starClass[1] = c[1];
}

void Star::addCompanion(Star* companion,size_t distance){
	companions.push_back({companion,distance});
}

const std::vector<std::pair<Star*,size_t>> Star::getCompanions() const{
	return companions;
}

size_t Star::getTemperature() const{
	return temperature;
}

const char* Star::getStarClass() const{
	return starClass;
}

bool Star::isStar() const{
	return true;
}
