#include "AstralObject.h"

AstralObject::AstralObject(size_t r) : radius(r){}

bool AstralObject::isStar() const{
	return false;
}

bool AstralObject::isWorld() const{
	return true;
}

size_t AstralObject::getRadius() const{
	return radius;
}
