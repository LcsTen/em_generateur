#ifndef star_h
#define star_h

#include "AstralObject.h"

#include <stddef.h>
#include <vector>

class Star : public AstralObject{
	private:
		size_t temperature;
		char starClass[2];
		std::vector<std::pair<Star*,size_t>> companions;
		
	public:
		Star(size_t t,size_t r,char c[2]);
		virtual ~Star() = default;
		
		void addCompanion(Star* companion,size_t distance);
		const std::vector<std::pair<Star*,size_t>> getCompanions() const;
		size_t getTemperature() const;
		const char* getStarClass() const;
		bool isStar() const;
};

#endif // star_h
