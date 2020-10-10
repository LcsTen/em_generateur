#include "Living.h"

#include "general.h"

Living::Living(const std::vector<Trait>& pTraits) : traits(pTraits){
	size = 1;
	strength = 1;
	hunting = 1;
	stealth = 1;
	intelligence = 1;
	//complexity = traits.size();
	for(const Trait& trait : traits){
		checkTraitAdd(trait);
	}
}

Living::Living() : Living(std::vector<Trait>{}) {};

void Living::checkTraitAdd(const Trait& trait,int mult){
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

void Living::mutate(){
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
void Living::addRandom(){
	std::vector<Trait> candidates;
	for(const Trait& trait : Trait::getAllTraits()){
		if(find(traits,trait) == traits.end()){
			bool ok = true;
			for(const Trait& prerequisite : trait.getPrerequisites()){
				ok &= (find(traits,prerequisite) != traits.end());
			}
			if(ok){
				candidates.push_back(trait);
			}
		}
	}
	addTrait(candidates[randomInt(candidates.size())]);
}

// For a trait to be removed, it musn't be a prerequisite for another trait
void Living::removeRandom(){
	std::vector<Trait> candidates;
	for(const Trait& toBeRemoved : traits){
		bool ok = true;
		for(const Trait& aTrait : traits){
			const std::vector<Trait>& prerequisites = aTrait.getPrerequisites();
			ok &= (find(prerequisites,toBeRemoved) == prerequisites.end());
		}
		if(ok){
			candidates.push_back(toBeRemoved);
		}
	}
	removeTrait(candidates[randomInt(candidates.size())]);
}

void Living::addTrait(const Trait& trait){
	if(find(traits,trait) != traits.end()){
		return;
	}
	traits.push_back(trait);
	checkTraitAdd(trait);
}

void Living::removeTrait(const Trait& trait){
	std::vector<Trait>::const_iterator it = find(traits,trait);
	if(it == traits.end()){
		return;
	}
	traits.erase(it);
	checkTraitAdd(trait,-1);
}

int Living::getSize() const{
	return size;
}

int Living::getStrength() const{
	return strength;
}

int Living::getHunting() const{
	return hunting;
}

int Living::getStealth() const{
	return stealth;
}

int Living::getComplexity() const{
	return traits.size();
}