#ifndef trait_h
#define trait_h

enum class TraitFlag{
	SIZE = 1,
	STRENGTH = 2,
	HUNTING = 4,
	STEALTH = 8,
	INTELLIGENCE = 16
};

class Trait{
	private:
		std::string name;
		int id;
		int flags;
		std::vector<Trait&> prerequisites;
		
		static std::vector<Trait&> allTraits;
	
	public:
		Trait(const std::string& pName,int pFlags,const std::vector<Trait&>& pPrerequisites);
		Trait(const std::string& pName,int pFlags = 0);
	
		const std::string& getName() const;
		int getId() const;
		bool hasFlag(TraitFlag flag) const;
		const std::vector<Trait&>& getPrerequisites() const;
		
		static const std::vector<Trait&>& getAllTraits() const;
};

bool operator==(const Trait& a,const Trait& b);

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
Trait crafter("Crafter",TraitFlag::STRENGTH | TraitFlag::HUNTING | Trait::INTELLIGENCE,{brain,hands});

#endif // trait_h