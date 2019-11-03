#ifndef monde_hpp
#define monde_hpp

#include <string>
#include <vector>
#include "general.hpp"
#include "Entite.hpp"

class Monde : public Entite{
		
	public:
		Monde(std::string nom);
		Monde();
		
		Entite* creerEnfant(std::string nom) override;
		Entite* creerEnfant() override;
		
		int getPopulation() const override;
		
		std::string toString() const override;
};

#endif