#include "Living.h"

Creature::Creature(const std::vector<Trait&>& pTraits) : traits(pTraits){
	size = 1;
	strength = 1;
	hunting = 1;
	stealth = 1;
	intelligence = 1;
	//complexity = traits.size();
	for(const Trait& trait : traits){
		checkAddTrait(trait);
	}
}

Creature::Creature() : Creature({});

void checkTraitAdd(const Trait& trait,int mult){
	if(trait.hasFlag(TraitFlag::SIZE)){
		size += mult;
	}
	if(trait.hasFlag(TraitFlag::STRENGTH)){
		strength += mult;
	}
	if(trait.hasFlag(TraitFlag::HUNTING)){
		hunting += mult;
	}
	if(trait.hasFlag(TraitFlag::STEALTH)){
		stealth += mult;
	}
	if(trait.hasFlag(TraitFlag::INTELLIGENCE)){
		intelligence += mult;
	}
}

void Creature::mutate(){
	if(traits.empty()){
		addRandom();
	}else if(traits.size() == Trait::getAllTraits().size()){
		removeRandom();
	}else if(randomInt(2) == 0){
		addRandom();
	}else{
		removeRandom();
	}
}

// For a trait to be added, the creature must have all the necessary prerequisites
void Creature::addRandom(){
	std::vector<Trait&> candidates;
	for(const Trait& trait : Trait::getAllTraits()){
		if(traits.find(trait) == traits.end()){
			bool ok = true;
			for(const Trait& prerequisite : trait.getPrerequisites()){
				ok &= (traits.find(prerequisite) != traits.end());
			}
			if(ok){
				candidates.push_back(trait);
			}
		}
	}
	addTrait(candidates[randomInt(candidats.size())]);
}

// For a trait to be removed, it musn't be a prerequisite for another trait
void Creature::removeRandom(){
	std::vector<Trait&> candidates;
	for(const Trait& toBeRemoved : traits){
		bool ok = true;
		for(const Trait& aTrait : traits){
			const std::vector<Trait&>& prerequisites = aTrait.getPrerequisites();
			ok &= (prerequisites.find(toBeRemoved) == prerequisites.end());
		}
		if(ok){
			candidates.push_back(toBeRemoved);
		}
	}
	removeTrait(candidates[randomInt(candidats.size())]);
}

void Creature::addTrait(const Trait& trait){
	if(traits.find(trait) != traits.end()){
		return;
	}
	traits.push_back(trait);
	checkTraitAdd(trait);
}

void Creature::removeTrait(const Trait& trait){
	std::vector<Trait&>::iterator it = traits.find(trait);
	if(it == traits.end()){
		return;
	}
	traits.erase(it);
	checkTraitAdd(trait,-1);
}

int Creature::getSize() const{
	return size;
}

int Creature::getStrength() const{
	return strength;
}

int Creature::getHunting() const{
	return hunting;
}

int Creature::getStealth() const{
	return stealth;
}

int Creature::getComplexity() const{
	return traits.size();
}