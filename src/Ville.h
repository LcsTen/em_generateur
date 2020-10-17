#ifndef ville_h
#define ville_h

#include <string>

#include "Entite.h"
#include "Pays.h"

class Ville : public Entite {
		
	public:
		Ville(std::string nom,Pays& pays);
		
		Entite* creerEnfant(std::string nom) override;
		Entite* creerEnfant() override;
		
		int getPopulation() const override;
		
		std::string toString() const override;
};

#endif // ville_h
