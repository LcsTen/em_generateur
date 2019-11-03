#include "Groupe.hpp"

#include <iostream>

Groupe::Groupe(std::string nom,Ville& ville) : Entite(nom,ville) {
	/*_nom = nom;
	_ville = ville;*/
	population = randomInt(1000,10000);
}
	
Entite* Groupe::creerEnfant(std::string nom){
	return NULL;
}

Entite* Groupe::creerEnfant(){
	return creerEnfant("");
}
	
int Groupe::getPopulation() const{
	return population;
}

std::string Groupe::toString() const{
	//return "Groupe(nom: "+_nom+", ms: "+ms+", mp: "+mp+", fs: "+fs+", fp: "+fp+", population: "+std::to_string(getPopulation())+')';
	return "Groupe"+Entite::toString();
}

/*std::ostream& Groupe::print(std::ostream& out) const{
	return out << toString();
}

std::ostream& operator<<(std::ostream& out,const Groupe g){
	return g.print(out);
}*/