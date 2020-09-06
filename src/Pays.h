#ifndef pays_h
#define pays_h

#include <string>
#include <vector>
#include "general.h"
#include "Monde.h"
#include "Entite.h"

class Pays : public Entite {
	
	public:
		Pays(std::string nom,Monde& _monde);
		
		Entite* creerEnfant(std::string nom) override;
		Entite* creerEnfant() override;
		
		int getPopulation() const override;
		
		std::string toString() const override;
};

#endif // pays_h