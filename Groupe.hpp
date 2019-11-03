#ifndef groupe_hpp
#define groupe_hpp

#include <string>
#include <vector>
#include "general.hpp"
#include "Entite.hpp"
#include "Ville.hpp"

class Groupe : public Entite{
	private:
		int population = 0;
		
	public:
		Groupe(std::string nom,Ville& ville);
		
		Entite* creerEnfant(std::string nom) override;
		Entite* creerEnfant() override;
		
		int getPopulation() const override;
		
		std::string toString() const override;
};

#endif