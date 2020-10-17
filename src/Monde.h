#ifndef monde_h
#define monde_h

#include <string>

#include "Entite.h"
#include "Map.h"
#include "Ecology.h"

class Monde : public Entite{
	private:
		Map map;
		Ecology eco;
		
	public:
		Monde(std::string nom,size_t lin,size_t col);
		Monde(std::string nom);
		Monde(size_t lin,size_t col);
		Monde();
		
		Entite* creerEnfant(std::string nom) override;
		Entite* creerEnfant() override;
		
		int getPopulation() const override;
		const Map& getMap() const;
		
		std::string toString() const override;
};

#endif // monde_h
