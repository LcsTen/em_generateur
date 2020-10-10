#include "Trait.h"

/*static*/ std::vector<Trait> Trait::allTraits = {};

Trait::Trait(const std::string& pName,int pFlags,const std::vector<Trait>& pPrerequisites) : name(pName), flags(pFlags), prerequisites(pPrerequisites){
	static int nextId = 1;
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

bool Trait::hasFlag(TraitFlag flag) const{
	return ((flags & flag) != 0);
}

const std::vector<Trait>& Trait::getPrerequisites() const{
	return prerequisites;
}

/*static*/ const std::vector<Trait>& Trait::getAllTraits() {
	return allTraits;
}

bool operator==(const Trait& a,const Trait& b){
	return (a.getId() == b.getId());
}

// Size-related traits
Trait insect("Insect",TraitFlag::SIZE);
Trait small("Small",TraitFlag::SIZE,{insect});
Trait medium("Medium",TraitFlag::SIZE,{small});
Trait big("Big",TraitFlag::SIZE,{medium});
Trait titan("Titan",TraitFlag::SIZE,{big});

// Legs-related traits affecting hunting and stealth abilities
Trait legs("Legs",TraitFlag::HUNTING | TraitFlag::STEALTH);
Trait runner("Runner",TraitFlag::HUNTING | TraitFlag::STEALTH,{legs});
Trait sprinter("Sprinter",TraitFlag::HUNTING | TraitFlag::STEALTH,{runner});

// Combat- and defense-related traits, affecting strength ability
Trait horn("Horn",TraitFlag::STRENGTH);
Trait sting("Sting",TraitFlag::STRENGTH);
Trait poisonous("Poisonous",TraitFlag::STRENGTH,{sting});
Trait paralyzing("Paralyzing",TraitFlag::STRENGTH,{sting});
Trait claws("Claws",TraitFlag::STRENGTH,{legs});
Trait tusks("Tusks",TraitFlag::STRENGTH);
Trait hands("Hands",TraitFlag::STRENGTH);

// Hunting-related traits
Trait smell("Smell",TraitFlag::HUNTING);

// Stealth-related traits, affecting stealth by avoiding predators or outrun them
Trait burrow("Burrow",TraitFlag::STEALTH);
Trait reflexes("Reflexes",TraitFlag::STEALTH);

// Eyes-related traits, affecting hunting and stealth abilities
Trait eyes("Eyes",TraitFlag::HUNTING | TraitFlag::STEALTH);
Trait binocularVision("Binocular Vision",TraitFlag::HUNTING,{eyes});
Trait sideVision("Side Vision",TraitFlag::STEALTH,{eyes});

// Brain-related traits, affecting intelligence among others
Trait brain("Brain",TraitFlag::INTELLIGENCE);
Trait strategist("Strategist",TraitFlag::STRENGTH | TraitFlag::HUNTING | TraitFlag::INTELLIGENCE,{brain});
Trait social("Social",TraitFlag::INTELLIGENCE,{brain});
Trait packHunter("Pack hunter",TraitFlag::HUNTING | TraitFlag::INTELLIGENCE,{social});
Trait swarmHunter("Swarm hunter",TraitFlag::HUNTING | TraitFlag::INTELLIGENCE,{packHunter});
Trait crafter("Crafter",TraitFlag::STRENGTH | TraitFlag::HUNTING | TraitFlag::INTELLIGENCE,{brain,hands});