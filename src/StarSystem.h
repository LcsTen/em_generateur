#ifndef star_system_h
#define star_system_h

#include "Star.h"
#include "World.h"

#include <string>
#include <vector>

class StarSystem{
	private:
		std::string name;
		std::vector<Star*> stars;
		std::vector<World*> worlds;
	
	public:
		StarSystem(std::string n);
		StarSystem();
		~StarSystem();
		
		std::vector<World*> getHabitableWorlds();
		std::string getName() const;
		const std::vector<Star*> getStars() const;
		const std::vector<World*> getWorlds() const;
};

#endif // star_system_h
