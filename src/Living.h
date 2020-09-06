#ifndef living_h
#define living_h

#include "Trait.h"

class Living{
	private:
		int size;
		int strength;
		int hunting;
		int stealth;
		int intelligence;
		std::vector<Trait&> traits;
		
		void addRandom();
		void removeRandom();
		
		void checkTraitAdd(const Trait& trait,int multiplier = 1);
	
	public:
		Living(const std::vector<Trait&>& pTraits);
		Living();
		
		void mutate();
		void addTrait(const Trait& trait);
		void removeTrait(const Trait& trait);
		
		int getSize() const;
		int getStrength() const;
		int getHunting() const;
		int getStealth() const;
		int getComplexity() const;
};

#endif // living_h