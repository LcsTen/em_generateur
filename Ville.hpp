#ifndef ville_hpp
#define ville_hpp

#include <string>
#include <vector>
#include "general.hpp"
#include "Entite.hpp"
#include "Pays.hpp"

class Ville : public Entite {
		
	public:
		Ville(std::string nom,Pays& pays);
		
		Entite* creerEnfant(std::string nom) override;
		Entite* creerEnfant() override;
		
		int getPopulation() const override;
		
		std::string toString() const override;
};

#endif