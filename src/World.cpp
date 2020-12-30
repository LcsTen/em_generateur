#include "World.h"

#include "general.h"

World::World(size_t r,AstralObject* o,size_t d) : AstralObject(r), orbiting(o), distance(d){
	name = generateName(10);
}

std::string World::getName() const{
	return name;
}

AstralObject* World::getOrbiting(){
	return orbiting;
}

size_t World::getDistance() const{
	return distance;
}

bool World::isWorld() const{
	return true;
}
