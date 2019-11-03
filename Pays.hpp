#ifndef pays_hpp
#define pays_hpp

#include <string>
#include <vector>
#include "general.hpp"
#include "Monde.hpp"
#include "Entite.hpp"

class Pays : public Entite {
	
	public:
		Pays(std::string nom,Monde& _monde);
		
		Entite* creerEnfant(std::string nom) override;
		Entite* creerEnfant() override;
		
		int getPopulation() const override;
		
		std::string toString() const override;
};

#endif