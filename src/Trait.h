#ifndef trait_h
#define trait_h

#include <string>
#include <vector>

enum TraitFlag{
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
		std::vector<Trait> prerequisites;
		
		static std::vector<Trait> allTraits;
	
	public:
		Trait(const std::string& pName,int pFlags,const std::vector<Trait>& pPrerequisites);
		Trait(const std::string& pName,int pFlags = 0);
	
		const std::string& getName() const;
		int getId() const;
		bool hasFlag(TraitFlag flag) const;
		const std::vector<Trait>& getPrerequisites() const;
		
		static const std::vector<Trait>& getAllTraits();
};

bool operator==(const Trait& a,const Trait& b);

// Size-related traits
extern Trait insect;
extern Trait small;
extern Trait medium;
extern Trait big;
extern Trait titan;

// Legs-related traits affecting hunting and stealth abilities
extern Trait legs;
extern Trait runner;
extern Trait sprinter;

// Combat- and defense-related traits, affecting strength ability
extern Trait horn;
extern Trait sting;
extern Trait poisonous;
extern Trait paralyzing;
extern Trait claws;
extern Trait tusks;
extern Trait hands;

// Hunting-related traits
extern Trait smell;

// Stealth-related traits, affecting stealth by avoiding predators or outrun them
extern Trait burrow;
extern Trait reflexes;

// Eyes-related traits, affecting hunting and stealth abilities
extern Trait eyes;
extern Trait binocularVision;
extern Trait sideVision;

// Brain-related traits, affecting intelligence among others
extern Trait brain;
extern Trait strategist;
extern Trait social;
extern Trait packHunter;
extern Trait swarmHunter;
extern Trait crafter;

#endif // trait_h
