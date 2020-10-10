#include "LivingGroup.h"

LivingGroup::LivingGroup(const Living& pLiving,int pPopulation,size_t pX,size_t pY) : living(pLiving), population(pPopulation), x(pX), y(pY) {}

bool LivingGroup::canMoveTo(const Tile& /*tile*/){
	return false;
}