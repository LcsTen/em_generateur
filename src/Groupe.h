#ifndef groupe_h
#define groupe_h

#include <string>
#include <vector>
#include "general.h"
#include "Entite.h"
#include "Ville.h"

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

#endif // groupe_h