#include "Monde.hpp"

#include "Pays.hpp"

#include <iostream>

Monde::Monde(std::string nom) : Entite(nom,*this) {
	int nbPays = randomInt(2,10);
	for(int i = 0;i < nbPays;i++){
		creerEnfant();
	}
}

Monde::Monde() : Monde(genererNom(10)) {}

Entite* Monde::creerEnfant(std::string nom){
	Pays* p = new Pays(nom,*this);
	enfants.push_back(p);
	return p;
}

Entite* Monde::creerEnfant(){
	return creerEnfant(genererNom(10));
}

int Monde::getPopulation() const{
	int res = 0;
	for(unsigned int i = 0;i < enfants.size();i++){
		res += enfants[i]->getPopulation();
	}
	return res;
}

/*std::string Monde::toString() const{
	return "Monde(nom: "+_nom+", ms: "+ms+", mp: "+mp+", fs: "+fs+", fp: "+fp+" pays.size(): "+std::to_string(pays.size())+", population: "+std::to_string(getPopulation())+')';
}*/

std::string Monde::toString() const{
	return "Monde"+Entite::toString();
}

/*std::ostream& Monde::print(std::ostream& out) const{
	return out << toString();
}

std::ostream& operator<<(std::ostream& out,const Monde m){
	return m.print(out);
}*/