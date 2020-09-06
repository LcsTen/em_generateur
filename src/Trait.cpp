#include "Trait.h"

Trait::Trait(const std::string& pName,int pFlags,const std::vector<Trait&>& pPrerequisites) : name(pName), flags(pFlags), prerequisites(pPrerequisites){
	static nextId = 1;
	id = nextId;
	nextId++;
	allTraits.push_back(*this);
}

Trait::Trait(const std::string& pName,int pFlags) : Trait(pName,pFlags,{}) {}

const std::string& Trait::getName() const{
	return name;
}

int Trait::getId() const{
	return id;
}

bool Trait::hasFlag(TraitFlag flag){
	return ((flags & flag) != 0);
}

static const std::vector<Trait&>& Trait::getAllTraits() const{
	return allTraits;
}

bool operator==(const Trait& a,const Trait& b){
	return (a.getId() == b.getId());
}